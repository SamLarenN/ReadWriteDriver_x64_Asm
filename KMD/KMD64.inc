macro CTL_CODE Name,DeviceType,Function,Method,Access {
Name=(((DeviceType) SHL 16) OR ((Access) SHL 14) OR ((Function) SHL 2) OR (Method))
}

IRP_MJ_CREATE			=	00h
IRP_MJ_CREATE_NAMED_PIPE	=	01h
IRP_MJ_CLOSE			=	02h
IRP_MJ_READ			=	03h
IRP_MJ_WRITE			=	04h
IRP_MJ_QUERY_INFORMATION	=	05h
IRP_MJ_SET_INFORMATION		=	06h
IRP_MJ_QUERY_EA 		=	07h
IRP_MJ_SET_EA			=	08h
IRP_MJ_FLUSH_BUFFERS		=	09h
IRP_MJ_QUERY_VOLUME_INFORMATION =	0Ah
IRP_MJ_SET_VOLUME_INFORMATION	=	0Bh
IRP_MJ_DIRECTORY_CONTROL	=	0Ch
IRP_MJ_FILE_SYSTEM_CONTROL	=	0Dh
IRP_MJ_DEVICE_CONTROL		=	0Eh
IRP_MJ_INTERNAL_DEVICE_CONTROL	=	0Fh
IRP_MJ_SHUTDOWN 		=	10h
IRP_MJ_LOCK_CONTROL		=	11h
IRP_MJ_CLEANUP			=	12h
IRP_MJ_CREATE_MAILSLOT		=	13h
IRP_MJ_QUERY_SECURITY		=	14h
IRP_MJ_SET_SECURITY		=	15h
IRP_MJ_POWER			=	16h
IRP_MJ_SYSTEM_CONTROL		=	17h
IRP_MJ_DEVICE_CHANGE		=	18h
IRP_MJ_QUERY_QUOTA		=	19h
IRP_MJ_SET_QUOTA		=	1Ah
IRP_MJ_PNP			=	1Bh
IRP_MJ_PNP_POWER		=	IRP_MJ_PNP	; Obsolete....
IRP_MJ_MAXIMUM_FUNCTION 	=	1Bh

POINTER_SIZE			=	8		; we are on long mode = 64 bit pointers

IRP_MJ_CREATE_OFFSET		=	POINTER_SIZE * IRP_MJ_CREATE
IRP_MJ_CREATE_NAMED_PIPE_OFFSET =	POINTER_SIZE * IRP_MJ_CREATE_NAMED_PIPE
IRP_MJ_CLOSE_OFFSET		=	POINTER_SIZE * IRP_MJ_CLOSE
IRP_MJ_READ_OFFSET		=	POINTER_SIZE * IRP_MJ_READ
IRP_MJ_WRITE_OFFSET		=	POINTER_SIZE * IRP_MJ_WRITE
IRP_MJ_QUERY_INFORMATION_OFFSET =	POINTER_SIZE * IRP_MJ_QUERY_INFORMATION
IRP_MJ_SET_INFORMATION_OFFSET	=	POINTER_SIZE * IRP_MJ_SET_INFORMATION
IRP_MJ_QUERY_EA_OFFSET		=	POINTER_SIZE * IRP_MJ_QUERY_EA
IRP_MJ_SET_EA_OFFSET		=	POINTER_SIZE * IRP_MJ_SET_EA
IRP_MJ_FLUSH_BUFFERS_OFFSET	=	POINTER_SIZE * IRP_MJ_FLUSH_BUFFERS
IRP_MJ_QUERY_VOLUME_INFORMATION_OFFSET	=	POINTER_SIZE * IRP_MJ_QUERY_VOLUME_INFORMATION
IRP_MJ_SET_VOLUME_INFORMATION_OFFSET	=	POINTER_SIZE * IRP_MJ_SET_VOLUME_INFORMATION
IRP_MJ_DIRECTORY_CONTROL_OFFSET 	=	POINTER_SIZE * IRP_MJ_DIRECTORY_CONTROL
IRP_MJ_FILE_SYSTEM_CONTROL_OFFSET	=	POINTER_SIZE * IRP_MJ_FILE_SYSTEM_CONTROL
IRP_MJ_DEVICE_CONTROL_OFFSET		=	POINTER_SIZE * IRP_MJ_DEVICE_CONTROL
IRP_MJ_INTERNAL_DEVICE_CONTROL_OFFSET	=	POINTER_SIZE * IRP_MJ_INTERNAL_DEVICE_CONTROL
IRP_MJ_SHUTDOWN_OFFSET		=	POINTER_SIZE * IRP_MJ_SHUTDOWN
IRP_MJ_LOCK_CONTROL_OFFSET	=	POINTER_SIZE * IRP_MJ_LOCK_CONTROL
IRP_MJ_CLEANUP_OFFSET		=	POINTER_SIZE * IRP_MJ_CLEANUP
IRP_MJ_CREATE_MAILSLOT_OFFSET	=	POINTER_SIZE * IRP_MJ_CREATE_MAILSLOT
IRP_MJ_QUERY_SECURITY_OFFSET	=	POINTER_SIZE * IRP_MJ_QUERY_SECURITY
IRP_MJ_SET_SECURITY_OFFSET	=	POINTER_SIZE * IRP_MJ_SET_SECURITY
IRP_MJ_POWER_OFFSET		=	POINTER_SIZE * IRP_MJ_POWER
IRP_MJ_SYSTEM_CONTROL_OFFSET	=	POINTER_SIZE * IRP_MJ_SYSTEM_CONTROL
IRP_MJ_DEVICE_CHANGE_OFFSET	=	POINTER_SIZE * IRP_MJ_DEVICE_CHANGE
IRP_MJ_QUERY_QUOTA_OFFSET	=	POINTER_SIZE * IRP_MJ_QUERY_QUOTA
IRP_MJ_SET_QUOTA_OFFSET 	=	POINTER_SIZE * IRP_MJ_SET_QUOTA
IRP_MJ_PNP_OFFSET		=	POINTER_SIZE * IRP_MJ_PNP
IRP_MJ_PNP_POWER_OFFSET 	=	POINTER_SIZE * IRP_MJ_PNP_POWER ; Obsolete....

FILE_DEVICE_UNKNOWN		=	00000022h

STATUS_SUCCESS			=	0
STATUS_UNSUCCESSFUL		=	0C0000001h
STATUS_NOT_IMPLEMENTED		=	0C0000002h

IO_NO_INCREMENT 		=	0

; Define I/O Request Packet (IRP) flags
IRP_NOCACHE			=	00000001h
IRP_PAGING_IO			=	00000002h
IRP_MOUNT_COMPLETION		=	00000002h
IRP_SYNCHRONOUS_API		=	00000004h
IRP_ASSOCIATED_IRP		=	00000008h
IRP_BUFFERED_IO 		=	00000010h
IRP_DEALLOCATE_BUFFER		=	00000020h
IRP_INPUT_OPERATION		=	00000040h
IRP_SYNCHRONOUS_PAGING_IO	=	00000040h
IRP_CREATE_OPERATION		=	00000080h
IRP_READ_OPERATION		=	00000100h
IRP_WRITE_OPERATION		=	00000200h
IRP_CLOSE_OPERATION		=	00000400h
IRP_DEFER_IO_COMPLETION 	=	00000800h
IRP_OB_QUERY_NAME		=	00001000h
IRP_HOLD_DEVICE_QUEUE		=	00002000h

; Define I/O request packet (IRP) alternate flags for allocation control.
IRP_QUOTA_CHARGED		=	01h
IRP_ALLOCATED_MUST_SUCCEED	=	02h
IRP_ALLOCATED_FIXED_SIZE	=	04h
IRP_LOOKASIDE_ALLOCATION	=	08h


struc	UNICODE_STRING
{
.Length 			rw	1
.MaximumLength			rw	1	; usually size in Lenght + 2
				rd	1	; padding
.Buffer 			rq	1	; pointer to string
}


struc	DRIVER_OBJECT
{
.Type				rw	1
.Size				rw	1
				rd	1	; padding
; The following links all of the devices created by a single driver
; together on a list, and the Flags word provides an extensible flag
; location for driver objects.
.DeviceObject			rq	1
.Flags				rd	1
				rd	1	; padding
; The following section describes where the driver is loaded. The count
; field is used to count the number of times the driver has had its
; registered reinitialization routine invoked.
.DriverStart			rq	1
.DriverSize			rq	1
.DriverSection			rq	1
.DriverExtension		rq	1
; The driver name field is used by the error log thread
; determine the name of the driver that an I/O request is/was bound.
.DriverName			UNICODE_STRING
; The following section is for registry support. This is a pointer
; to the path to the hardware information in the registry
.HardwareDatabase		rq	1	; PUNICODE_STRING
; The following section contains the optional pointer to an array of
; alternate entry points to a driver for "fast I/O" support. Fast I/O
; is performed by invoking the driver routine directly with separate
; parameters, rather than using the standard IRP call mechanism. Note
; that these functions may only be used for synchronous I/O, and when
; the file is cached.
.FastIoDispatch 		rq	1
; The following section describes the entry points to this particular
; driver. Note that the major function dispatch table must be the last
; field in the object so that it remains extensible.
.DriverInit			rq	1
.DriverStartIo			rq	1
.DriverUnload			rq	1
.MajorFunction			rq	IRP_MJ_MAXIMUM_FUNCTION + 1
}

struc IO_STATUS_BLOCK
{
.Status 			rd	1
				rd	1	; padding
label IO_STATUS_BLOCK.Pointer	qword
.Information			rq	1
}


; I/O Request Packet (IRP) definition
struc vIRP
{
.Type				rw	1
.Size				rw	1
				rd	1	; padding
; Define the common fields used to control the IRP.
; Define a pointer to the Memory Descriptor List (MDL) for this I/O
; request. This field is only used if the I/O is "direct I/O".
.MdlAddress			rq	1
; Flags word - used to remember various flags.
.Flags				rq	1	; offset 10h
; The following union is used for one of three purposes:
; 1. This IRP is an associated IRP. The field is a pointer to a master IRP.
; 2. This is the master IRP. The field is the count of the number of
;    IRPs which must complete (associated IRPs) before the master can complete.
; 3. This operation is being buffered and the field is the address of
;    the system space buffer.
label .AssociatedIrp.MasterIrp	qword		; offset 18h
label .AssociatedIrp.IrpCount	dword		; offset 18h
.AssociatedIrp.SystemBuffer	rq	1	; offset 18h
; Thread list entry - allows queueing the IRP to the thread pending I/O
; request packet list.
;// The type SINGLE_LIST_ENTRY is not suitable for use with SLISTs. For
;// WIN64, an entry on an SLIST is required to be 16-byte aligned, while a
;// SINGLE_LIST_ENTRY structure has only 8 byte alignment.
;// Therefore, all SLIST code should use the SLIST_ENTRY type instead of the
;// SINGLE_LIST_ENTRY type.
.ThreadListEntry		rq	2	; is it OK ?
; I/O status - final status of operation.
.IoStatus			IO_STATUS_BLOCK ; offset 30h
; Requestor mode - mode of the original requestor of this operation.
.RequestorMode			rb	1	; offset 40h
; Pending returned - TRUE if pending was initially returned as the
; status for this packet.
.PendingReturned		rb	1
; Stack state information.
.StackCount			rb	1
.CurrentLocation		rb	1
; Cancel - packet has been canceled.
.Cancel 			rb	1
; Cancel Irql - Irql at which the cancel spinlock was acquired.
.CancelIrql			rb	1
; ApcEnvironment - Used to save the APC environment at the time that the
; packet was initialized.
.ApcEnvironment 		rb	1
; Allocation control flags.
.AllocationFlags		rb	1
; User parameters.
.UserIosb			rq	1	; offset 48h
.UserEvent			rq	1	; offset 50h
label .Overlay.AsynchronousParameters.UserApcRoutine qword	; offset 58h
label .Overlay.AsynchronousParameters.UserApcContext qword at $+8	; offset 60h
.Overlay.AllocationSize 	rq	2	; offset 58h
; CancelRoutine - Used to contain the address of a cancel routine supplied
; by a device driver when the IRP is in a cancelable state.
.CancelRoutine			rq	1	; offset 68h
; Note that the UserBuffer parameter is outside of the stack so that I/O
; completion can copy data back into the user's address space without
; having to know exactly which service was being invoked. The length
; of the copy is stored in the second half of the I/O status block. If
; the UserBuffer field is NULL, then no copy is performed.
.UserBuffer			rq	1	; offset 70h
; Kernel structures
; The following section contains kernel structures which the IRP needs
; in order to place various work information in kernel controller system
; queues. Because the size and alignment cannot be controlled, they are
; placed here at the end so they just hang off and do not affect the
; alignment of other fields in the IRP.
; DeviceQueueEntry - The device queue entry field is used to
; queue the IRP to the device driver device queue.
.Tail.Overlay.DeviceQueueEntry: 		; offset 78h
; The following are available to the driver to use in
; whatever manner is desired, while the driver owns the packet.
.Tail.Overlay.DriverContext	rq	4	; offset 78h
; Thread - pointer to caller's Thread Control Block.
.Tail.Overlay.Thread		rq	1	; offset 98h
; Auxiliary buffer - pointer to any auxiliary buffer that is
; required to pass information to a driver that is not contained
; in a normal buffer.
.Tail.Overlay.AuxiliaryBuffer	rq	1	; offset A0h
; The following unnamed structure must be exactly identical
; to the unnamed structure used in the minipacket header used
; for completion queue entries.
; List entry - used to queue the packet to completion queue, among
; others.
.Tail.Overlay.ListEntry 	rq	2	; offset A8h
; Current stack location - contains a pointer to the current
; IO_STACK_LOCATION structure in the IRP stack. This field
; should never be directly accessed by drivers. They should
; use the standard functions.
label .Tail.Overlay.CurrentStackLocation	qword	; offset B8h
; Minipacket type.
.Tail.Overlay.PacketType	rd	1	; offset B8h
				rd	1	; padding
; Original file object - pointer to the original file object
; that was used to open the file. This field is owned by the
; I/O system and should not be used by any other drivers.
.Tail.Overlay.OriginalFileObject	rq	1	; offset C0h
; APC - This APC control block is used for the special kernel APC as
; well as for the caller's APC, if one was specified in the original
; argument list. If so, then the APC is reused for the normal APC for
; whatever mode the caller was in and the "special" routine that is
; invoked before the APC gets control simply deallocates the IRP.
label .Tail.Apc at .Tail.Overlay.DeviceQueueEntry
; CompletionKey - This is the key that is used to distinguish
; individual I/O operations initiated on a single file handle.
label .Tail.CompletionKey	qword at .Tail.Overlay.DeviceQueueEntry
}


struc	IO_STACK_LOCATION
{
.MajorFunction			rb	1	; 00h
.MinorFunction			rb	1	; 01h
.Flags				rb	1	; 02h
.Control			rb	1	; 03h
				rd	1	; padding
; The following user parameters are based on the service that is being
; invoked. Drivers and file systems can determine which set to use based
; on the above major and minor function codes.
; union Parameters				; 08h
; System service parameters for: NtCreateFile
; struct Create 				; 08h
.Parameters.Create.SecurityContext	rq	1	; 08h PTR IO_SECURITY_CONTEXT
.Parameters.Create.Options		rd	1	; 10h
					rd	1	; padding
.Parameters.Create.FileAttributes	rw	1	; 18h POINTER_ALIGNMENT
.Parameters.Create.ShareAccess		rw	1	; 1Ah
					rd	1	; padding
.Parameters.Create.EaLength		rq	1	; 20h POINTER_ALIGNMENT
; ends
; System service parameters for: NtReadFile
; struc Read					; 08h
label .Parameters.Read.Length	dword at 8	; 08h
label .Parameters.Read.Key	qword at 10h	; 10h POINTER_ALIGNMENT
label .Parameters.Read.ByteOffset dqword at 18h ; LARGE_INTEGER <> ; 18h
; ends
; System service parameters for:  NtWriteFile
; struct Write					; 08h
label .Parameters.Write.Length	dword at 8	; 08h
label .Parameters.Write.KeyKey	qword at 10h	; 10h POINTER_ALIGNMENT
label .Parameters.Write.ByteOffset dqword at 18h	; LARGE_INTEGER <> ; 18h
; ends
; System service parameters for:  NtQueryInformationFile
; struct QueryFile
label .Parameters.QueryFile.Length	dword at 8	; 08h
label .Parameters.QueryFile.FileInformationClass	qword at 10h	; 10h POINTER_ALIGNMENT
; ends
; System service parameters for: NtFlushBuffersFile
; No extra user-supplied parameters.
; System service parameters for: NtDeviceIoControlFile
; Note that the user's output buffer is stored in the UserBuffer field
; and the user's input buffer is stored in the SystemBuffer field.
;struct DeviceIoControl
label .Parameters.DeviceIoControl.OutputBufferLength	dword at 8
label .Parameters.DeviceIoControl.InputBufferLength	dword at 10h
label .Parameters.DeviceIoControl.IoControlCode 	dword at 18h
label .Parameters.DeviceIoControl.Type3InputBuffer	qword at 20h
; ends
;ends	 ; Parameters
; Save a pointer to this device driver's device object for this request
; so it can be passed to the completion routine if needed.
.DeviceObject			rq	1		; offset 28h
; The following location contains a pointer to the file object for this
.FileObject			rq	1
; The following routine is invoked depending on the flags in the above
; flags field.
.CompletionRoutine		rq	1
; The following is used to store the address of the context parameter
; that should be passed to the CompletionRoutine.
.Context			rq	1		; offset 40h
}
