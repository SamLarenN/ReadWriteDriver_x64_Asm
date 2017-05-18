;*******************************************
;* (X) SamLaren 2017                       *
;*******************************************
;* x64_Asm_Driver               	   *
;*					   *
;* release v1.0 	    18/05/2017	   *
;*					   *
;*******************************************


format	     PE64 native 5.02 at 10000H
entry	     DriverEntry

include 'KMD\KMD64.inc'
include 'INCLUDE\win64ax.inc'

CTL_CODE ReadReq, FILE_DEVICE_UNKNOWN, 0x701, 0, 0	; CTL_CODE(FILE_DEVICE_UNKNOWN, 0x701, METHOD\
							; _BUFFERED, FILE_SPECIAL_ACCESS
CTL_CODE WriteReq, FILE_DEVICE_UNKNOWN, 0x702, 0, 0
CTL_CODE ModuleReq, FILE_DEVICE_UNKNOWN, 0x703, 0, 0

;C struct for Read or Write
;typedef struct _REQUEST
;{
;	 DWORD Address; 	0x0   0
;	 DWORD Size;		0x4   4
;	 DWORD ProcessId;	0x8   8
;	 DWORD Value;		0xC   12
;}REQUEST, *PREQUEST;


; C struct for module request:
;typedef struct _REQUESTMODULE
;{
;	 DWORD ModuleBase;
;	 DWORD ProcessId;
;}REQUESTMODULE, *PREQUESTMODULE;


virtual at 0
DriverObject	DRIVER_OBJECT	    ; Create a virtual DRIVER_OBJECT struct with 0 as base
end virtual

virtual at 0
pIRP		vIRP
end virtual

virtual at 0
iosl		IO_STACK_LOCATION
end virtual

virtual at 0
us		UNICODE_STRING
end virtual

section '.text' code readable executable notpageable

align 10h
DriverEntry:
;RCX = pDriverObject
;RDX = pusRegistryPath

	push	rbx
	push	rsi
	push	rdi
	sub	rsp, 8*(4+8)	; 12 local qwords on stack
	mov	rbx, rcx	; RBX = pDriverObject (RBX is not changed during API calls)
	invoke	DbgPrintEx, 77, 0, strout, loaded

	mov	rax, DriverUnload
	mov	[rbx + DriverObject.DriverUnload], rax	  ; [pDriverObject + DriverUnload] = DriverUnload
	mov	rax, DispatchCreate
	mov	[rbx + DriverObject.MajorFunction + IRP_MJ_CREATE_OFFSET], rax	 ; Set DispatchCreate
	mov	rax, DispatchClose
	mov	[rbx + DriverObject.MajorFunction + IRP_MJ_CLOSE_OFFSET], rax	 ; Set DispatchClose
	mov	rax, IOCTL
	mov	[rbx + DriverObject.MajorFunction + IRP_MJ_DEVICE_CONTROL_OFFSET], rax	 ; Set IOCTL function.
	mov	rax, ImageLoadCallback
	invoke	PsSetLoadImageNotifyRoutine, rax	; Set LoadImageNotifyRoutine

	lea	rdi, [rsp + 8*(4+6)]	     ; [rsp + 8*(4+6)] = (UNICODE_STRING*)strDriverName
	lea	rsi, [strDriverName]
	invoke	RtlInitUnicodeString, rdi, rsi

	lea	rdi, [rsp + 8*(4+4)]	     ; [rsp + 8*(4+4)] = (UNICODE_STRING*)strSymbolic
	lea	rsi, [strSymbolic]
	invoke	RtlInitUnicodeString, rdi, rsi

	lea	rsi, [rsp + 8*(4+6)]	     ; (UNICODE_STRING*)strDriverName
	lea	rdi, [rsp + 8*(4+2)]	     ; (QWORD*)
	invoke	IoCreateDevice, rbx, 0, rsi, 22h, 100h, FALSE, rdi     ; Create IoDevice, pointer in rdi.
	test	eax, eax
	jnz	@ReturnLoader		   ; If it fails, return the error code in EAX.

	lea	rsi, [rsp + 8*(4+2)]	   ; pDeviceObject	 (Get pointer to DeviceObject)
	or	dword[rsi + 30h], 10h	   ; pDeviceObject->Flags   (Set flags for I/O)
	mov	eax, 80h
	not	eax
	and	dword[rsi + 30h], eax				   ;(Set flags for I/O)

	lea	rsi, [rsp + 8*(4+4)]	     ; strSymbolic
	lea	rdi, [rsp + 8*(4+6)]	     ; strDriverName
	invoke	IoCreateSymbolicLink, rsi, rdi

@ReturnLoader:
	add	rsp, 8*(4+8)
	pop	rdi
	pop	rsi
	pop	rbx
	ret


align 10h
DriverUnload:
; RCX = pDriverObject
	push	rbx
	push	rsi
	push	rdi
	sub	rsp, 8*(2+4)
	mov	rbx, rcx	  ; Save pDriverObject address in RBX, RBX is not affected by API
	invoke	DbgPrintEx, 77, 0, strout, unloaded

	mov	rax, ImageLoadCallback
	invoke	PsRemoveLoadImageNotifyRoutine, rax	 ; Important to remove ImageNotifyRoutine to avoid BSOD

	lea	rdi, [rsp + 8*(2+2)]
	mov	rsi, strSymbolic
	invoke	RtlInitUnicodeString, rdi, rsi
	lea	rsi, [rsp + 8*(2+2)]
	invoke	IoDeleteSymbolicLink, rsi

	mov	rax, [rbx + DriverObject.DeviceObject]
	invoke	IoDeleteDevice, rax

	add	rsp, 8*(2+4)
	pop	rdi
	pop	rsi
	pop	rbx
	ret

; Function to handle Input/Output Control.
align 10h
IOCTL:
; RCX = pDeviceObject
; RDX = pIRP

	push	rbp
	push	rsi
	push	rdi
	push	rcx
	push	rdx
	push	rbx
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15

	sub	rsp, 8*2
	mov	rbx, rdx	; save pIRP in rbx
	invoke	DbgPrintEx, 77, 0, strout, ioctlCall

	mov	rsi, [rbx + pIRP.Tail.Overlay.CurrentStackLocation]   ; Get (IO_STACK_LOCATION*)CurrentStackLocation
	test	rsi, rsi					      ; in RSI.
	jnz	@1	    ; If found go to @1, else continue.

	mov	dword[rbx + pIRP.IoStatus.Status], STATUS_UNSUCCESSFUL

	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT
	mov	eax, STATUS_UNSUCCESSFUL       ; LEAVE UNSUCCESSFUL
	jmp	@RetIo

@1:
	mov	eax, [rsi + iosl.Parameters.DeviceIoControl.IoControlCode]    ; EAX = ControlCode
	cmp	eax, ReadReq	    ; Check for ReadRequest
	je	@2
	cmp	eax, WriteReq	    ; Check for WriteRequest
	je	@2
	cmp	eax, ModuleReq	    ; Check for ModuleRequest
	je	@@2

	; If it is bad control code:
	mov	[rbx + pIRP.IoStatus.Status], STATUS_UNSUCCESSFUL	; Bad control code.
	mov	[rbx + pIRP.IoStatus.Information], 0			; No output buffer.
	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT
	mov	eax, STATUS_UNSUCCESSFUL				; LEAVE UNSUCCESSFUL
	jmp	@RetIo


@2:
	mov	rdi, [rbx + pIRP.AssociatedIrp.SystemBuffer]		; Get input buffer (struct from usermode) in RDI

	mov	eax, dword[rdi + 8]	; DWORD processid
	lea	rdx, [rsp]
	invoke	PsLookupProcessByProcessId, eax, rdx	 ; [rsp] = PEPROCESS*	(Get EPROCESS struct of process)
	test	eax, eax
	jz	@3

	; If it fails to find Peproc:
	invoke	DbgPrintEx, 77, 0, hex, eax
	mov	[rbx + pIRP.IoStatus.Status], STATUS_UNSUCCESSFUL	; No Peproc
	mov	[rbx + pIRP.IoStatus.Information], 0			; No output buffer
	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT
	mov	eax, STATUS_UNSUCCESSFUL				; LEAVE UNSUCCESSFUL
	jmp	@RetIo


@3:
	; Check if it is read or write:
	mov	eax, [rsi + iosl.Parameters.DeviceIoControl.IoControlCode]    ; EAX = ControlCode
	cmp	eax, ReadReq
	je	@ReadMem

;@WriteMem:
	mov	rax, [rsp]	       ; We need to save [rsp] in rax because the stack will be affected\
				       ; when pushing args.
	xor	r8, r8
	mov	r8d, dword[rdi + 4]
	push	r8		       ; PUSH (DWORD)SizeToRead

	xor	r8, r8
	mov	r8d, dword[rdi]
	push	r8		       ; PUSH (DWORD)dst

	lea	r8, [rdi + 12]
	push	r8		       ; PUSH (DWORD)src

	push	rax		       ; PUSH (QWORD)(PEPROCESS)peProc
	jmp	@4		       ; Jump to call.

; For Mem, we exchange dst and src args:
@ReadMem:
	mov	rax, [rsp]	       ; We need to save [rsp] in rax because the stack will be affected\
				       ; when pushing args.
	xor	r8, r8
	mov	r8d, dword[rdi + 4]
	push	r8		       ; PUSH (DWORD)SizeToRead

	lea	r8, [rdi + 12]
	push	r8		       ; PUSH (QWORD)dst  (This is a x64 address) rdi + 12 = (QWORD)Address

	xor	r8, r8
	mov	r8d, dword[rdi]
	push	r8		       ; PUSH (DWORD)src

	push	rax		       ; PUSH (QWORD)(PEPROCESS)peProc

@4:
	call	KernelRead
	add	rsp, 8*4		; Restore stack from args


	mov	rdx, [rsp]				; [rsp] = PEPROCESS*
	invoke	ObDereferenceObject, rdx		; rdx = PEPROCESS  (Dereference EPROCESS struct)


	mov	[rbx + pIRP.AssociatedIrp.SystemBuffer], rdi	  ; Update output buffer (structure sent to usermode)


	mov	dword[rbx + pIRP.IoStatus.Status], STATUS_SUCCESS
	mov	eax, [rsi + iosl.Parameters.DeviceIoControl.InputBufferLength]
	mov	dword[rbx + pIRP.IoStatus.Information], eax		 ; Set output buffer size,
	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT 		 ; same size as input buffer.

	mov	eax, STATUS_SUCCESS
	jmp	@RetIo


; Get Module:
@@2:
	mov	rdi, [rbx + pIRP.AssociatedIrp.SystemBuffer]		; Get input buffer in RDI

	mov	rax, [moduleBase]
	mov	dword[rdi], eax
	mov	rax, [pId]
	mov	dword[rdi + 4], eax

	mov	[rbx + pIRP.AssociatedIrp.SystemBuffer], rdi	  ; Set pointer to output buffer.


	mov	dword[rbx + pIRP.IoStatus.Status], STATUS_SUCCESS
	mov	dword[rbx + pIRP.IoStatus.Information], 8
	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT 		 ; same size as input buffer.

	mov	eax, STATUS_SUCCESS


@RetIo:
	add	rsp, 8*2
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	rbx
	pop	rdx
	pop	rcx
	pop	rdi
	pop	rsi
	pop	rbp
	ret




align 10h
KernelRead:
; qword[rbp + 40] = Size to be read			(DWORD Size) Rest of bits in qword are zero
; qword[rbp + 32] = Address to read to			(void* dst)
; qword[rbp + 24] = Address to read from		(void* src)
; qword[rbp + 16] = peProc				(PEPROCESS peProc)

; Return status code in EAX

	push	rbp
	mov	rbp, rsp
	mov	rax, qword[rbp + 16]
	invoke	KeAttachProcess, qword[rbp + 16]
	jmp	@R1
	invoke	MmIsAddressValid, qword[rbp + 24]
	test	eax, eax
	jnz	@R1

	; If the src address is not valid:
	invoke	KeDetachProcess, qword[rbp + 16]
	invoke	DbgPrintEx, 77, 0, strout, InvalidAddr
	mov	eax, STATUS_UNSUCCESSFUL
	jmp	@R_Ret

@R1:
	invoke	RtlCopyMemory, qword[rbp + 32], qword[rbp + 24], qword[rbp + 40]

	invoke	KeDetachProcess, qword[rbp + 16]
	mov	eax, STATUS_SUCCESS

@R_Ret:
	mov	rsp, rbp
	pop	rbp
	ret


; Function which automatically executes when a new module is loaded.
; Parameters are:
;  _In_opt_ PUNICODE_STRING FullImageName,
;  _In_     HANDLE	    ProcessId,
;  _In_     PIMAGE_INFO     ImageInfo,
;  _In_     BOOLEAN	    Create

; This function compares all FullImageName.
;      If correct Image is found:
;	  Save ImageBase from IMAGE_INFO struct
;	  Save ProcessId
align 10h
ImageLoadCallback:

	;mov	 [FullImageName], rcx
	;mov	 [ProcessId], rdx
	;mov	 [ImageInfo], r8

	push	rbx
	push	rsi
	push	rdi
	sub	rsp, 8*4
	mov	rbx, rcx
	mov	[rsp + 8*2], rdx      ; Save pointer to ProcessId on stack
	mov	[rsp + 8*3], r8       ; Save pointer to IMAGE_INFO on stack

	;invoke  DbgPrintEx, 77, 0, wstrout, rbx
	mov	rsi, modPath
	lea	rdi, [rsp]
	invoke	RtlInitUnicodeString, rdi, rsi	   ; WSTR* -> PUNICODE_STRING

	lea	rsi, [rsp]
	;invoke  DbgPrintEx, 77, 0, wstrout, rsi

	lea	rsi, [rsp]
	invoke	RtlCompareUnicodeString, rbx, rsi, 0   ; Compare FullImageName with modPath
	test	eax, eax
	jnz	@@@1

	mov	rsi, [rsp + 8*2]
	mov	[pId], rsi		  ; Save ProcessId
	mov	rsi, [rsp + 8*3]
	mov	rsi, [rsi + 4*2]	  ; Get ImageBase (second element in struct) of 32bit IMAGE_INFO struct (4*2)
	mov	[moduleBase], rsi	  ; Save ImageBase

@@@1:
	add	rsp, 8*4
	pop	rdi
	pop	rsi
	pop	rbx
	ret





align 10h
DispatchCreate:
; RCX = pDeviceObject
; RDX = pIRP

	push	rbx
	mov	rbx, rdx	; save pIRP in rbx
	invoke	DbgPrintEx, 77, 0, strout, dispCreate

	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT
	mov	eax, STATUS_SUCCESS
	pop	rbx
	ret

align 10h
DispatchClose:
; RCX = pDeviceObject
; RDX = pIRP

	push	rbx
	mov	rbx, rdx	; save pIRP in rbx
	invoke	DbgPrintEx, 77, 0, strout, dispClose

	invoke	IoCompleteRequest, rbx, IO_NO_INCREMENT
	mov	eax, STATUS_SUCCESS
	pop	rbx
	ret


align 10h
strDriverName		du '\Device\AsmDriver',0	     ; WSTR*

align 10h
strSymbolic		du '\DosDevices\AsmDriver',0	     ; WSTR*

align 10h
modPath 		du '\csgo\bin\client.dll',0	; WSTR*

section '.data' readable writeable
strout		db '%s',13,10,0
wstrout 	db '%wZ',13,10,0
hex		db '%X',13,10,0
wchar		db '%S',13,10,0
loaded		db 'Driver Loader Called!',0
unloaded	db 'Unloader Called!',0
dispCreate	db 'Dispatch Create Called!',0
dispClose	db 'Dispatch Close Called!',0
ioctlCall	db 'IOCTL Have Been Called!',0
NoStackLoc	db 'Could not find stack location, Error: %X',0
NoPeproc	db 'Could not get PEPROCESS, ERROR:',0
InvalidAddr	db 'Source Address not valid!',0

moduleBase	dq ?
pId		dq ?

section '.import' import readable
    library ntoskrnl, 'ntoskrnl.exe'

    import ntoskrnl, RtlInitUnicodeString, 'RtlInitUnicodeString', \
	   IoDeleteSymbolicLink, 'IoDeleteSymbolicLink', \
	   IoDeleteDevice, 'IoDeleteDevice', \
	   IoCreateDevice, 'IoCreateDevice', \
	   IoCreateSymbolicLink, 'IoCreateSymbolicLink', \
	   IoCompleteRequest, 'IoCompleteRequest', \
	   ZwCreateFile, 'ZwCreateFile', \
	   ZwOpenFile, 'ZwOpenFile', \
	   ZwReadFile, 'ZwReadFile', \
	   ZwWriteFile, 'ZwWriteFile', \
	   ZwClose, 'ZwClose', \
	   ZwQuerySystemInformation, 'ZwQuerySystemInformation', \
	   ExAllocatePool, 'ExAllocatePool', \
	   ExFreePool, 'ExFreePool', \
	   RtlCopyMemory, 'RtlCopyMemory',\
	   DbgPrintEx, 'DbgPrintEx',\
	   PsLookupProcessByProcessId, 'PsLookupProcessByProcessId',\
	   KeAttachProcess, 'KeAttachProcess',\
	   KeDetachProcess, 'KeDetachProcess',\
	   MmIsAddressValid, 'MmIsAddressValid',\
	   ObDereferenceObject, 'ObDereferenceObject',\
	   PsGetProcessWow64Process, 'PsGetProcessWow64Process',\
	   PsGetProcessPeb, 'PsGetProcessPeb',\
	   PsSetLoadImageNotifyRoutine, 'PsSetLoadImageNotifyRoutine',\
	   PsRemoveLoadImageNotifyRoutine, 'PsRemoveLoadImageNotifyRoutine',\
	   RtlEqualUnicodeString, 'RtlEqualUnicodeString',\
	   RtlCompareUnicodeString, 'RtlCompareUnicodeString'



section '.reloc' fixups data readable discardable
