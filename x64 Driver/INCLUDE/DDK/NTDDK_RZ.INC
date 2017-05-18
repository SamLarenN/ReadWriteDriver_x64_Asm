
; FASM SOURCE FILE
; http://flatassembler.net

; written by @L.CHEMIST (Andrey A. Meshkov)
; maalchemist@gmail.com
; maa-mail@yandex.ru

; ------------------------------------------------------------------------------

TYPEDEF PBUS_HANDLER, PVOID
TYPEDEF PCALLBACK_OBJECT, PVOID
TYPEDEF PDEVICE_HANDLER_OBJECT, PVOID
TYPEDEF PEPROCESS, PVOID
TYPEDEF PETHREAD, PVOID
TYPEDEF PIO_TIMER, PVOID
TYPEDEF PKINTERRUPT, PVOID
TYPEDEF PKTHREAD, PVOID
TYPEDEF PRKTHREAD, PVOID
TYPEDEF POBJECT_TYPE, PVOID
TYPEDEF PPEB, PVOID

TYPEDEF KPROCESSOR_MODE, CCHAR

TYPEDEF MODE, enum
    KernelMode	= 0
    UserMode	= 1
    MaximumMode = 2
TYPEDEF PMODE, PVOID

TYPEDEF PKNORMAL_ROUTINE, PVOID

TYPEDEF PKKERNEL_ROUTINE, PVOID

TYPEDEF PKRUNDOWN_ROUTINE, PVOID

TYPEDEF PKSYNCHRONIZE_ROUTINE, PVOID

TYPEDEF PKTRANSFER_ROUTINE, PVOID

TYPEDEF PKAPC, PVOID
TYPEDEF PRKAPC, PVOID
struct KAPC
    Type	   CSHORT ?
    Size	   CSHORT ?
    Spare0	   ULONG ?
    Thread	   PKTHREAD ?
    ApcListEntry   LIST_ENTRY ?
    KernelRoutine  PKKERNEL_ROUTINE ?
    RundownRoutine PKRUNDOWN_ROUTINE ?
    NormalRoutine  PKNORMAL_ROUTINE ?
    NormalContext  PVOID ?

    ; //
    ; // N.B. The following two members MUST be together.
    ; //

    SystemArgument1 PVOID ?
    SystemArgument2 PVOID ?
    ApcStateIndex   CCHAR ?
    ApcMode	    KPROCESSOR_MODE ?
    Inserted	    BOOLEAN ?
		    PADDING 1, 1
ends

TYPEDEF PKDEFERRED_ROUTINE, PVOID

TYPEDEF KDPC_IMPORTANCE, enum
    LowImportance    = 0
    MediumImportance = 1
    HighImportance   = 2
TYPEDEF PKDPC_IMPORTANCE, PVOID

TYPEDEF PKDPC, PVOID
TYPEDEF PRKDPC, PVOID
struct KDPC
    Type	    CSHORT ?
    Number	    UCHAR ?
    Importance	    UCHAR ?
		    PADDING 4, 0
    DpcListEntry    LIST_ENTRY ?
    DeferredRoutine PKDEFERRED_ROUTINE ?
    DeferredContext PVOID ?
    SystemArgument1 PVOID ?
    SystemArgument2 PVOID ?
    Lock	    PULONG_PTR ?
ends

TYPEDEF PMDL, PVOID
struct MDL
    Next	   PMDL ?
    Size	   CSHORT ?
    MdlFlags	   CSHORT ?
		   PADDING 4, 0
    Process	   PEPROCESS ?
    MappedSystemVa PVOID ?
    StartVa	   PVOID ?
    ByteCount	   ULONG ?
    ByteOffset	   ULONG ?
ends

TYPEDEF PDISPATCHER_HEADER, PVOID
struct DISPATCHER_HEADER
    Type	 UCHAR ?
    Absolute	 UCHAR ?
    Size	 UCHAR ?
    Inserted	 UCHAR ?
    SignalState  LONG ?
    WaitListHead LIST_ENTRY ?
ends

TYPEDEF PKEVENT, PVOID
TYPEDEF PRKEVENT, PVOID
struct KEVENT
    Header DISPATCHER_HEADER ?
ends

TYPEDEF PACCESS_TOKEN, PVOID

TYPEDEF PSECURITY_DESCRIPTOR, PVOID

TYPEDEF PSID, PVOID

TYPEDEF ACCESS_MASK, ULONG
TYPEDEF PACCESS_MASK, PVOID

TYPEDEF SECURITY_IMPERSONATION_LEVEL, enum
    SecurityAnonymous	   = 0
    SecurityIdentification = 1
    SecurityImpersonation  = 2
    SecurityDelegation	   = 3
TYPEDEF PSECURITY_IMPERSONATION_LEVEL, PVOID

SECURITY_MAX_IMPERSONATION_LEVEL = SecurityDelegation
SECURITY_MIN_IMPERSONATION_LEVEL = SecurityAnonymous
DEFAULT_IMPERSONATION_LEVEL	 = SecurityImpersonation

SECURITY_DYNAMIC_TRACKING      = (TRUE)
SECURITY_STATIC_TRACKING       = (FALSE)

TYPEDEF SECURITY_CONTEXT_TRACKING_MODE, BOOLEAN
TYPEDEF PSECURITY_CONTEXT_TRACKING_MODE, PVOID

struct SECURITY_QUALITY_OF_SERVICE
    Length		ULONG ?
    ImpersonationLevel	SECURITY_IMPERSONATION_LEVEL ?
    ContextTrackingMode SECURITY_CONTEXT_TRACKING_MODE ?
    EffectiveOnly	BOOLEAN ?
			PADDING 2, 2
ends
TYPEDEF PSECURITY_QUALITY_OF_SERVICE, PVOID

TYPEDEF SECURITY_INFORMATION, ULONG
TYPEDEF PSECURITY_INFORMATION, PVOID

TYPEDEF KSPIN_LOCK, ULONG_PTR
TYPEDEF PKSPIN_LOCK, PVOID

TYPEDEF DEVICE_TYPE, ULONG

FILE_DEVICE_BEEP		= 0x00000001
FILE_DEVICE_CD_ROM		= 0x00000002
FILE_DEVICE_CD_ROM_FILE_SYSTEM	= 0x00000003
FILE_DEVICE_CONTROLLER		= 0x00000004
FILE_DEVICE_DATALINK		= 0x00000005
FILE_DEVICE_DFS 		= 0x00000006
FILE_DEVICE_DISK		= 0x00000007
FILE_DEVICE_DISK_FILE_SYSTEM	= 0x00000008
FILE_DEVICE_FILE_SYSTEM 	= 0x00000009
FILE_DEVICE_INPORT_PORT 	= 0x0000000a
FILE_DEVICE_KEYBOARD		= 0x0000000b
FILE_DEVICE_MAILSLOT		= 0x0000000c
FILE_DEVICE_MIDI_IN		= 0x0000000d
FILE_DEVICE_MIDI_OUT		= 0x0000000e
FILE_DEVICE_MOUSE		= 0x0000000f
FILE_DEVICE_MULTI_UNC_PROVIDER	= 0x00000010
FILE_DEVICE_NAMED_PIPE		= 0x00000011
FILE_DEVICE_NETWORK		= 0x00000012
FILE_DEVICE_NETWORK_BROWSER	= 0x00000013
FILE_DEVICE_NETWORK_FILE_SYSTEM = 0x00000014
FILE_DEVICE_NULL		= 0x00000015
FILE_DEVICE_PARALLEL_PORT	= 0x00000016
FILE_DEVICE_PHYSICAL_NETCARD	= 0x00000017
FILE_DEVICE_PRINTER		= 0x00000018
FILE_DEVICE_SCANNER		= 0x00000019
FILE_DEVICE_SERIAL_MOUSE_PORT	= 0x0000001a
FILE_DEVICE_SERIAL_PORT 	= 0x0000001b
FILE_DEVICE_SCREEN		= 0x0000001c
FILE_DEVICE_SOUND		= 0x0000001d
FILE_DEVICE_STREAMS		= 0x0000001e
FILE_DEVICE_TAPE		= 0x0000001f
FILE_DEVICE_TAPE_FILE_SYSTEM	= 0x00000020
FILE_DEVICE_TRANSPORT		= 0x00000021
FILE_DEVICE_UNKNOWN		= 0x00000022
FILE_DEVICE_VIDEO		= 0x00000023
FILE_DEVICE_VIRTUAL_DISK	= 0x00000024
FILE_DEVICE_WAVE_IN		= 0x00000025
FILE_DEVICE_WAVE_OUT		= 0x00000026
FILE_DEVICE_8042_PORT		= 0x00000027
FILE_DEVICE_NETWORK_REDIRECTOR	= 0x00000028
FILE_DEVICE_BATTERY		= 0x00000029
FILE_DEVICE_BUS_EXTENDER	= 0x0000002a
FILE_DEVICE_MODEM		= 0x0000002b
FILE_DEVICE_VDM 		= 0x0000002c
FILE_DEVICE_MASS_STORAGE	= 0x0000002d
FILE_DEVICE_SMB 		= 0x0000002e
FILE_DEVICE_KS			= 0x0000002f
FILE_DEVICE_CHANGER		= 0x00000030
FILE_DEVICE_SMARTCARD		= 0x00000031
FILE_DEVICE_ACPI		= 0x00000032
FILE_DEVICE_DVD 		= 0x00000033
FILE_DEVICE_FULLSCREEN_VIDEO	= 0x00000034
FILE_DEVICE_DFS_FILE_SYSTEM	= 0x00000035
FILE_DEVICE_DFS_VOLUME		= 0x00000036
FILE_DEVICE_SERENUM		= 0x00000037
FILE_DEVICE_TERMSRV		= 0x00000038
FILE_DEVICE_KSEC		= 0x00000039
FILE_DEVICE_FIPS		= 0x0000003A
FILE_DEVICE_INFINIBAND		= 0x0000003B

TYPEDEF PIO_STATUS_BLOCK, PVOID
struct IO_STATUS_BLOCK
    union
	Status	NTSTATUS ?
	Pointer PVOID ?
    ends

    Information ULONG_PTR ?
ends

TYPEDEF PIO_APC_ROUTINE, PVOID

TYPEDEF FILE_INFORMATION_CLASS, enum
    FileDirectoryInformation	   = 1
    FileFullDirectoryInformation   = 2
    FileBothDirectoryInformation   = 3
    FileBasicInformation	   = 4	; wdm
    FileStandardInformation	   = 5	; wdm
    FileInternalInformation	   = 6
    FileEaInformation		   = 7
    FileAccessInformation	   = 8
    FileNameInformation 	   = 9
    FileRenameInformation	   = 10
    FileLinkInformation 	   = 11
    FileNamesInformation	   = 12
    FileDispositionInformation	   = 13
    FilePositionInformation	   = 14 ; wdm
    FileFullEaInformation	   = 15
    FileModeInformation 	   = 16
    FileAlignmentInformation	   = 17
    FileAllInformation		   = 18
    FileAllocationInformation	   = 19
    FileEndOfFileInformation	   = 20 ; wdm
    FileAlternateNameInformation   = 21
    FileStreamInformation	   = 22
    FilePipeInformation 	   = 23
    FilePipeLocalInformation	   = 24
    FilePipeRemoteInformation	   = 25
    FileMailslotQueryInformation   = 26
    FileMailslotSetInformation	   = 27
    FileCompressionInformation	   = 28
    FileObjectIdInformation	   = 29
    FileCompletionInformation	   = 30
    FileMoveClusterInformation	   = 31
    FileQuotaInformation	   = 32
    FileReparsePointInformation    = 33
    FileNetworkOpenInformation	   = 34
    FileAttributeTagInformation    = 35
    FileTrackingInformation	   = 36
    FileIdBothDirectoryInformation = 37
    FileIdFullDirectoryInformation = 38
    FileValidDataLengthInformation = 39
    FileShortNameInformation	   = 40
    FileMaximumInformation	   = 41
TYPEDEF PFILE_INFORMATION_CLASS, PVOID

TYPEDEF FS_INFORMATION_CLASS, enum
    FileFsVolumeInformation	= 1
    FileFsLabelInformation	= 2
    FileFsSizeInformation	= 3
    FileFsDeviceInformation	= 4
    FileFsAttributeInformation	= 5
    FileFsControlInformation	= 6
    FileFsFullSizeInformation	= 7
    FileFsObjectIdInformation	= 8
    FileFsDriverPathInformation = 9
    FileFsMaximumInformation	= 10
TYPEDEF PFS_INFORMATION_CLASS, PVOID

TYPEDEF INTERFACE_TYPE, enum
    InterfaceTypeUndefined = -1
    Internal		   = 0
    Isa 		   = 1
    Eisa		   = 2
    MicroChannel	   = 3
    TurboChannel	   = 4
    PCIBus		   = 5
    VMEBus		   = 6
    NuBus		   = 7
    PCMCIABus		   = 8
    CBus		   = 9
    MPIBus		   = 10
    MPSABus		   = 11
    ProcessorInternal	   = 12
    InternalPowerBus	   = 13
    PNPISABus		   = 14
    PNPBus		   = 15
    MaximumInterfaceType   = 16
TYPEDEF PINTERFACE_TYPE, PVOID

TYPEDEF SYSTEM_POWER_STATE, enum
    PowerSystemUnspecified = 0
    PowerSystemWorking	   = 1
    PowerSystemSleeping1   = 2
    PowerSystemSleeping2   = 3
    PowerSystemSleeping3   = 4
    PowerSystemHibernate   = 5
    PowerSystemShutdown    = 6
    PowerSystemMaximum	   = 7
TYPEDEF PSYSTEM_POWER_STATE, PVOID

POWER_SYSTEM_MAXIMUM = 7

TYPEDEF POWER_ACTION, enum
    PowerActionNone	     = 0
    PowerActionReserved      = 1
    PowerActionSleep	     = 2
    PowerActionHibernate     = 3
    PowerActionShutdown      = 4
    PowerActionShutdownReset = 5
    PowerActionShutdownOff   = 6
    PowerActionWarmEject     = 7
TYPEDEF PPOWER_ACTION, PVOID

TYPEDEF DEVICE_POWER_STATE, enum
    PowerDeviceUnspecified = 0
    PowerDeviceD0	   = 1
    PowerDeviceD1	   = 2
    PowerDeviceD2	   = 3
    PowerDeviceD3	   = 4
    PowerDeviceMaximum	   = 5
TYPEDEF PDEVICE_POWER_STATE, PVOID

TYPEDEF PPOWER_STATE, PVOID
struct POWER_STATE
    union ; POWER_STATE
	SystemState SYSTEM_POWER_STATE ?
	DeviceState DEVICE_POWER_STATE ?
    ends
ends

TYPEDEF POWER_STATE_TYPE, enum
    SystemPowerState = 0
    DevicePowerState = 1
TYPEDEF PPOWER_STATE_TYPE, PVOID

TYPEDEF PCM_PARTIAL_RESOURCE_DESCRIPTOR, PVOID

TYPEDEF PCM_PARTIAL_RESOURCE_LIST, PVOID

TYPEDEF PCM_FULL_RESOURCE_DESCRIPTOR, PVOID

TYPEDEF PCM_RESOURCE_LIST, PVOID

TYPEDEF PIO_RESOURCE_DESCRIPTOR, PVOID

TYPEDEF PIO_RESOURCE_LIST, PVOID

TYPEDEF PIO_RESOURCE_REQUIREMENTS_LIST, PVOID

TYPEDEF PKSTART_ROUTINE, PVOID

TYPEDEF PKDEVICE_QUEUE, PVOID
TYPEDEF PRKDEVICE_QUEUE, PVOID
struct KDEVICE_QUEUE
    Type	   CSHORT ?
    Size	   CSHORT ?
		   PADDING 4, 0
    DeviceListHead LIST_ENTRY ?
    Lock	   KSPIN_LOCK ?
    Busy	   BOOLEAN ?
		   PADDING 3, 3
ends

TYPEDEF PKDEVICE_QUEUE_ENTRY, PVOID
TYPEDEF PRKDEVICE_QUEUE_ENTRY, PVOID
struct KDEVICE_QUEUE_ENTRY
    DeviceListEntry LIST_ENTRY ?
    SortKey	    ULONG ?
    Inserted	    BOOLEAN ?
		    PADDING 3, 3
ends

TYPEDEF PKSERVICE_ROUTINE, PVOID

IO_NO_INCREMENT 		= 0

TYPEDEF PACCESS_STATE, PVOID

IO_TYPE_ADAPTER 		= 0x00000001
IO_TYPE_CONTROLLER		= 0x00000002
IO_TYPE_DEVICE			= 0x00000003
IO_TYPE_DRIVER			= 0x00000004
IO_TYPE_FILE			= 0x00000005
IO_TYPE_IRP			= 0x00000006
IO_TYPE_MASTER_ADAPTER		= 0x00000007
IO_TYPE_OPEN_PACKET		= 0x00000008
IO_TYPE_TIMER			= 0x00000009
IO_TYPE_VPB			= 0x0000000a
IO_TYPE_ERROR_LOG		= 0x0000000b
IO_TYPE_ERROR_MESSAGE		= 0x0000000c
IO_TYPE_DEVICE_OBJECT_EXTENSION = 0x0000000d

IRP_MJ_CREATE			= 0x00
IRP_MJ_CREATE_NAMED_PIPE	= 0x01
IRP_MJ_CLOSE			= 0x02
IRP_MJ_READ			= 0x03
IRP_MJ_WRITE			= 0x04
IRP_MJ_QUERY_INFORMATION	= 0x05
IRP_MJ_SET_INFORMATION		= 0x06
IRP_MJ_QUERY_EA 		= 0x07
IRP_MJ_SET_EA			= 0x08
IRP_MJ_FLUSH_BUFFERS		= 0x09
IRP_MJ_QUERY_VOLUME_INFORMATION = 0x0a
IRP_MJ_SET_VOLUME_INFORMATION	= 0x0b
IRP_MJ_DIRECTORY_CONTROL	= 0x0c
IRP_MJ_FILE_SYSTEM_CONTROL	= 0x0d
IRP_MJ_DEVICE_CONTROL		= 0x0e
IRP_MJ_INTERNAL_DEVICE_CONTROL	= 0x0f
IRP_MJ_SHUTDOWN 		= 0x10
IRP_MJ_LOCK_CONTROL		= 0x11
IRP_MJ_CLEANUP			= 0x12
IRP_MJ_CREATE_MAILSLOT		= 0x13
IRP_MJ_QUERY_SECURITY		= 0x14
IRP_MJ_SET_SECURITY		= 0x15
IRP_MJ_POWER			= 0x16
IRP_MJ_SYSTEM_CONTROL		= 0x17
IRP_MJ_DEVICE_CHANGE		= 0x18
IRP_MJ_QUERY_QUOTA		= 0x19
IRP_MJ_SET_QUOTA		= 0x1a
IRP_MJ_PNP			= 0x1b
IRP_MJ_PNP_POWER		= IRP_MJ_PNP	  ; // Obsolete....
IRP_MJ_MAXIMUM_FUNCTION 	= 0x1b

TYPEDEF PIO_DPC_ROUTINE, PVOID

TYPEDEF PIO_TIMER_ROUTINE, PVOID

TYPEDEF PDRIVER_INITIALIZE, PVOID

TYPEDEF PDRIVER_REINITIALIZE, PVOID

TYPEDEF PDRIVER_CANCEL, PVOID

TYPEDEF PDRIVER_DISPATCH, PVOID

TYPEDEF PDRIVER_STARTIO, PVOID

TYPEDEF PDRIVER_UNLOAD, PVOID

TYPEDEF PDRIVER_ADD_DEVICE, PVOID

TYPEDEF PFAST_IO_CHECK_IF_POSSIBLE, PVOID

TYPEDEF PFAST_IO_READ, PVOID

TYPEDEF PFAST_IO_WRITE, PVOID

TYPEDEF PFAST_IO_QUERY_BASIC_INFO, PVOID

TYPEDEF PFAST_IO_QUERY_STANDARD_INFO, PVOID

TYPEDEF PFAST_IO_LOCK, PVOID

TYPEDEF PFAST_IO_UNLOCK_SINGLE, PVOID

TYPEDEF PFAST_IO_UNLOCK_ALL, PVOID

TYPEDEF PFAST_IO_UNLOCK_ALL_BY_KEY, PVOID

TYPEDEF PFAST_IO_DEVICE_CONTROL, PVOID

TYPEDEF PFAST_IO_ACQUIRE_FILE, PVOID

TYPEDEF PFAST_IO_RELEASE_FILE, PVOID

TYPEDEF PFAST_IO_DETACH_DEVICE, PVOID

TYPEDEF PFAST_IO_QUERY_NETWORK_OPEN_INFO, PVOID

TYPEDEF PFAST_IO_MDL_READ, PVOID

TYPEDEF PFAST_IO_MDL_READ_COMPLETE, PVOID

TYPEDEF PFAST_IO_PREPARE_MDL_WRITE, PVOID

TYPEDEF PFAST_IO_MDL_WRITE_COMPLETE, PVOID

TYPEDEF PFAST_IO_ACQUIRE_FOR_MOD_WRITE, PVOID

TYPEDEF PFAST_IO_RELEASE_FOR_MOD_WRITE, PVOID

TYPEDEF PFAST_IO_ACQUIRE_FOR_CCFLUSH, PVOID

TYPEDEF PFAST_IO_RELEASE_FOR_CCFLUSH, PVOID

TYPEDEF PFAST_IO_READ_COMPRESSED, PVOID

TYPEDEF PFAST_IO_WRITE_COMPRESSED, PVOID

TYPEDEF PFAST_IO_MDL_READ_COMPLETE_COMPRESSED, PVOID

TYPEDEF PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED, PVOID

TYPEDEF PFAST_IO_QUERY_OPEN, PVOID

TYPEDEF PFAST_IO_DISPATCH, PVOID
struct FAST_IO_DISPATCH
    SizeOfFastIoDispatch	  ULONG ?
				  PADDING 4, 0
    FastIoCheckIfPossible	  PFAST_IO_CHECK_IF_POSSIBLE ?
    FastIoRead			  PFAST_IO_READ ?
    FastIoWrite 		  PFAST_IO_WRITE ?
    FastIoQueryBasicInfo	  PFAST_IO_QUERY_BASIC_INFO ?
    FastIoQueryStandardInfo	  PFAST_IO_QUERY_STANDARD_INFO ?
    FastIoLock			  PFAST_IO_LOCK ?
    FastIoUnlockSingle		  PFAST_IO_UNLOCK_SINGLE ?
    FastIoUnlockAll		  PFAST_IO_UNLOCK_ALL ?
    FastIoUnlockAllByKey	  PFAST_IO_UNLOCK_ALL_BY_KEY ?
    FastIoDeviceControl 	  PFAST_IO_DEVICE_CONTROL ?
    AcquireFileForNtCreateSection PFAST_IO_ACQUIRE_FILE ?
    ReleaseFileForNtCreateSection PFAST_IO_RELEASE_FILE ?
    FastIoDetachDevice		  PFAST_IO_DETACH_DEVICE ?
    FastIoQueryNetworkOpenInfo	  PFAST_IO_QUERY_NETWORK_OPEN_INFO ?
    AcquireForModWrite		  PFAST_IO_ACQUIRE_FOR_MOD_WRITE ?
    MdlRead			  PFAST_IO_MDL_READ ?
    MdlReadComplete		  PFAST_IO_MDL_READ_COMPLETE ?
    PrepareMdlWrite		  PFAST_IO_PREPARE_MDL_WRITE ?
    MdlWriteComplete		  PFAST_IO_MDL_WRITE_COMPLETE ?
    FastIoReadCompressed	  PFAST_IO_READ_COMPRESSED ?
    FastIoWriteCompressed	  PFAST_IO_WRITE_COMPRESSED ?
    MdlReadCompleteCompressed	  PFAST_IO_MDL_READ_COMPLETE_COMPRESSED ?
    MdlWriteCompleteCompressed	  PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED ?
    FastIoQueryOpen		  PFAST_IO_QUERY_OPEN ?
    ReleaseForModWrite		  PFAST_IO_RELEASE_FOR_MOD_WRITE ?
    AcquireForCcFlush		  PFAST_IO_ACQUIRE_FOR_CCFLUSH ?
    ReleaseForCcFlush		  PFAST_IO_RELEASE_FOR_CCFLUSH ?
ends

TYPEDEF PDRIVER_CONTROL, PVOID

TYPEDEF PIO_SECURITY_CONTEXT, PVOID
struct IO_SECURITY_CONTEXT
    SecurityQos       PSECURITY_QUALITY_OF_SERVICE ?
    AccessState       PACCESS_STATE ?
    DesiredAccess     ACCESS_MASK ?
    FullCreateOptions ULONG ?
ends

MAXIMUM_VOLUME_LABEL_LENGTH  = (32 * sizeof.WCHAR) ; // 32 characters

TYPEDEF PVPB, PVOID
struct VPB
    Type	      CSHORT ?
    Size	      CSHORT ?
    Flags	      USHORT ?
    VolumeLabelLength USHORT ? ; // in bytes
    DeviceObject      PVOID ? ; PDEVICE_OBJECT ?
    RealDevice	      PVOID ? ; PDEVICE_OBJECT ?
    SerialNumber      ULONG ?
    ReferenceCount    ULONG ?
    VolumeLabel       WCHAR (MAXIMUM_VOLUME_LABEL_LENGTH / sizeof.WCHAR) dup (?)
ends

TYPEDEF PWAIT_CONTEXT_BLOCK, PVOID
struct WAIT_CONTEXT_BLOCK
    WaitQueueEntry	 KDEVICE_QUEUE_ENTRY ?
    DeviceRoutine	 PDRIVER_CONTROL ?
    DeviceContext	 PVOID ?
    NumberOfMapRegisters ULONG ?
			 PADDING 4, 0
    DeviceObject	 PVOID ?
    CurrentIrp		 PVOID ?
    BufferChainingDpc	 PKDPC ?
ends

TYPEDEF PDEVICE_OBJECT, PVOID
struct DEVICE_OBJECT
    Type	    CSHORT ?
    Size	    USHORT ?
    ReferenceCount  LONG ?
    DriverObject    PVOID ? ; PDRIVER_OBJECT ?
    NextDevice	    PDEVICE_OBJECT ?
    AttachedDevice  PDEVICE_OBJECT ?
    CurrentIrp	    PVOID ? ; P_IRP ?
    Timer	    PIO_TIMER ?
    Flags	    ULONG ?			 ; // See above:  DO_...
    Characteristics ULONG ?			 ; // See ntioapi:  FILE_...
    Vpb 	    PVPB ?
    DeviceExtension PVOID ?
    DeviceType	    DEVICE_TYPE ?
    StackSize	    CCHAR ?
		    PADDING 3, 3
    union ; Queue
	Queue.ListEntry LIST_ENTRY ?
	Queue.Wcb	WAIT_CONTEXT_BLOCK ?
    ends ; Queue
    AlignmentRequirement ULONG ?
    DeviceQueue 	 KDEVICE_QUEUE ?
    Dpc 		 KDPC ?

    ; //
    ; //  The following field is for exclusive use by the filesystem to keep
    ; //  track of the number of Fsp threads currently using the device
    ; //

    ActiveThreadCount	  ULONG ?
			  PADDING 4, 0
    SecurityDescriptor	  PSECURITY_DESCRIPTOR ?
    DeviceLock		  KEVENT ?

    SectorSize		  USHORT ?
    Spare1		  USHORT ?

    DeviceObjectExtension PVOID ? ; PDEVOBJ_EXTENSION ?
    Reserved		  PVOID ?
ends
VIRTDEF V_DEVICE_OBJECT, DEVICE_OBJECT

TYPEDEF PDEVOBJ_EXTENSION, PVOID
struct DEVOBJ_EXTENSION
    Type CSHORT ?
    Size USHORT ?
	 PADDING 4, 0

    ; //
    ; // Public part of the DeviceObjectExtension structure
    ; //

    DeviceObject PDEVICE_OBJECT ?		; // owning device object
ends

DRVO_UNLOAD_INVOKED		= 0x00000001
DRVO_LEGACY_DRIVER		= 0x00000002
DRVO_BUILTIN_DRIVER		= 0x00000004	; // Driver objects for Hal, PnP Mgr

DRVO_REINIT_REGISTERED		= 0x00000008
DRVO_INITIALIZED		= 0x00000010
DRVO_BOOTREINIT_REGISTERED	= 0x00000020
DRVO_LEGACY_RESOURCES		= 0x00000040

TYPEDEF PDRIVER_EXTENSION, PVOID
struct DRIVER_EXTENSION
    ; //
    ; // Back pointer to Driver Object
    ; //

    DriverObject PVOID ? ; PDRIVER_OBJECT ?

    ; //
    ; // The AddDevice entry point is called by the Plug & Play manager
    ; // to inform the driver when a new device instance arrives that this
    ; // driver must control.
    ; //

    AddDevice PDRIVER_ADD_DEVICE ?

    ; //
    ; // The count field is used to count the number of times the driver has
    ; // had its registered reinitialization routine invoked.
    ; //

    Count ULONG ?
	  PADDING 4, 0

    ; //
    ; // The service name field is used by the pnp manager to determine
    ; // where the driver related info is stored in the registry.
    ; //

    ServiceKeyName UNICODE_STRING ?

    ; //
    ; // Note: any new shared fields get added here.
    ; //
ends

TYPEDEF PDRIVER_OBJECT, PVOID
struct DRIVER_OBJECT
    Type	     CSHORT ?
    Size	     CSHORT ?
		     PADDING 4, 0

    ; //
    ; // The following links all of the devices created by a single driver
    ; // together on a list, and the Flags word provides an extensible flag
    ; // location for driver objects.
    ; //

    DeviceObject     PDEVICE_OBJECT ?
    Flags	     ULONG ?
		     PADDING 4, 0

    ; //
    ; // The following section describes where the driver is loaded.  The count
    ; // field is used to count the number of times the driver has had its
    ; // registered reinitialization routine invoked.
    ; //

    DriverStart      PVOID ?
    DriverSize	     ULONG ?
		     PADDING 4, 0
    DriverSection    PVOID ?
    DriverExtension  PDRIVER_EXTENSION ?

    ; //
    ; // The driver name field is used by the error log thread
    ; // determine the name of the driver that an I/O request is/was bound.
    ; //

    DriverName	     UNICODE_STRING ?

    ; //
    ; // The following section is for registry support.  Thise is a pointer
    ; // to the path to the hardware information in the registry
    ; //

    HardwareDatabase PUNICODE_STRING ?

    ; //
    ; // The following section contains the optional pointer to an array of
    ; // alternate entry points to a driver for "fast I/O" support.  Fast I/O
    ; // is performed by invoking the driver routine directly with separate
    ; // parameters, rather than using the standard IRP call mechanism.  Note
    ; // that these functions may only be used for synchronous I/O, and when
    ; // the file is cached.
    ; //

    FastIoDispatch   PFAST_IO_DISPATCH ?

    ; //
    ; // The following section describes the entry points to this particular
    ; // driver.  Note that the major function dispatch table must be the last
    ; // field in the object so that it remains extensible.
    ; //

    DriverInit	     PDRIVER_INITIALIZE ?
    DriverStartIo    PDRIVER_STARTIO ?
    DriverUnload     PDRIVER_UNLOAD ?
    MajorFunction    PDRIVER_DISPATCH (IRP_MJ_MAXIMUM_FUNCTION + 1) dup (?)
ends
VIRTDEF V_DRIVER_OBJECT, DRIVER_OBJECT

TYPEDEF PSECTION_OBJECT_POINTERS, PVOID
struct SECTION_OBJECT_POINTERS
    DataSectionObject  PVOID ?
    SharedCacheMap     PVOID ?
    ImageSectionObject PVOID ?
ends

TYPEDEF PIO_COMPLETION_CONTEXT, PVOID
struct IO_COMPLETION_CONTEXT
    Port PVOID ?
    Key  PVOID ?
ends

FO_FILE_OPEN			= 0x00000001
FO_SYNCHRONOUS_IO		= 0x00000002
FO_ALERTABLE_IO 		= 0x00000004
FO_NO_INTERMEDIATE_BUFFERING	= 0x00000008
FO_WRITE_THROUGH		= 0x00000010
FO_SEQUENTIAL_ONLY		= 0x00000020
FO_CACHE_SUPPORTED		= 0x00000040
FO_NAMED_PIPE			= 0x00000080
FO_STREAM_FILE			= 0x00000100
FO_MAILSLOT			= 0x00000200
FO_GENERATE_AUDIT_ON_CLOSE	= 0x00000400
FO_DIRECT_DEVICE_OPEN		= 0x00000800
FO_FILE_MODIFIED		= 0x00001000
FO_FILE_SIZE_CHANGED		= 0x00002000
FO_CLEANUP_COMPLETE		= 0x00004000
FO_TEMPORARY_FILE		= 0x00008000
FO_DELETE_ON_CLOSE		= 0x00010000
FO_OPENED_CASE_SENSITIVE	= 0x00020000
FO_HANDLE_CREATED		= 0x00040000
FO_FILE_FAST_IO_READ		= 0x00080000
FO_RANDOM_ACCESS		= 0x00100000
FO_FILE_OPEN_CANCELLED		= 0x00200000
FO_VOLUME_OPEN			= 0x00400000
FO_FILE_OBJECT_HAS_EXTENSION	= 0x00800000
FO_REMOTE_ORIGIN		= 0x01000000

TYPEDEF PFILE_OBJECT, PVOID
struct FILE_OBJECT
    Type		 CSHORT ?
    Size		 CSHORT ?
			 PADDING 4, 0
    DeviceObject	 PDEVICE_OBJECT ?
    Vpb 		 PVPB ?
    FsContext		 PVOID ?
    FsContext2		 PVOID ?
    SectionObjectPointer PSECTION_OBJECT_POINTERS ?
    PrivateCacheMap	 PVOID ?
    FinalStatus 	 NTSTATUS ?
			 PADDING 4, 0
    RelatedFileObject	 PFILE_OBJECT ?
    LockOperation	 BOOLEAN ?
    DeletePending	 BOOLEAN ?
    ReadAccess		 BOOLEAN ?
    WriteAccess 	 BOOLEAN ?
    DeleteAccess	 BOOLEAN ?
    SharedRead		 BOOLEAN ?
    SharedWrite 	 BOOLEAN ?
    SharedDelete	 BOOLEAN ?
    Flags		 ULONG ?
    FileName		 UNICODE_STRING ?
    CurrentByteOffset	 LARGE_INTEGER ?
    Waiters		 ULONG ?
    Busy		 ULONG ?
    LastLock		 PVOID ?
    Lock		 KEVENT ?
    Event		 KEVENT ?
    CompletionContext	 PIO_COMPLETION_CONTEXT ?
ends

IRP_NOCACHE			= 0x00000001
IRP_PAGING_IO			= 0x00000002
IRP_MOUNT_COMPLETION		= 0x00000002
IRP_SYNCHRONOUS_API		= 0x00000004
IRP_ASSOCIATED_IRP		= 0x00000008
IRP_BUFFERED_IO 		= 0x00000010
IRP_DEALLOCATE_BUFFER		= 0x00000020
IRP_INPUT_OPERATION		= 0x00000040
IRP_SYNCHRONOUS_PAGING_IO	= 0x00000040
IRP_CREATE_OPERATION		= 0x00000080
IRP_READ_OPERATION		= 0x00000100
IRP_WRITE_OPERATION		= 0x00000200
IRP_CLOSE_OPERATION		= 0x00000400

IRP_DEFER_IO_COMPLETION 	= 0x00000800
IRP_OB_QUERY_NAME		= 0x00001000
IRP_HOLD_DEVICE_QUEUE		= 0x00002000
IRP_RETRY_IO_COMPLETION 	= 0x00004000
IRP_CLASS_CACHE_OPERATION	= 0x00008000
IRP_SET_USER_EVENT		= IRP_CLOSE_OPERATION

IRP_QUOTA_CHARGED		= 0x01
IRP_ALLOCATED_MUST_SUCCEED	= 0x02
IRP_ALLOCATED_FIXED_SIZE	= 0x04
IRP_LOOKASIDE_ALLOCATION	= 0x08

TYPEDEF PIRP, PVOID
struct T_IRP
    Type CSHORT ?
    Size USHORT ?
	 PADDING 4, 0

    ; //
    ; // Define the common fields used to control the IRP.
    ; //

    ; //
    ; // Define a pointer to the Memory Descriptor List (MDL) for this I/O
    ; // request.  This field is only used if the I/O is "direct I/O".
    ; //

    MdlAddress PMDL ?

    ; //
    ; // Flags word - used to remember various flags.
    ; //

    Flags ULONG ?
	  PADDING 4, 0

    ; //
    ; // The following union is used for one of three purposes:
    ; //
    ; //    1. This IRP is an associated IRP.  The field is a pointer to a master
    ; //       IRP.
    ; //
    ; //    2. This is the master IRP.	The field is the count of the number of
    ; //       IRPs which must complete (associated IRPs) before the master can
    ; //       complete.
    ; //
    ; //    3. This operation is being buffered and the field is the address of
    ; //       the system space buffer.
    ; //

    union ; AssociatedIrp
	AssociatedIrp.MasterIrp    PIRP ?
	AssociatedIrp.IrpCount	   LONG ?
	AssociatedIrp.SystemBuffer PVOID ?
    ends ; AssociatedIrp

    ; //
    ; // Thread list entry - allows queueing the IRP to the thread pending I/O
    ; // request packet list.
    ; //

    ThreadListEntry LIST_ENTRY ?

    ; //
    ; // I/O status - final status of operation.
    ; //

    IoStatus IO_STATUS_BLOCK ?

    ; //
    ; // Requestor mode - mode of the original requestor of this operation.
    ; //

    RequestorMode KPROCESSOR_MODE ?

    ; //
    ; // Pending returned - TRUE if pending was initially returned as the
    ; // status for this packet.
    ; //

    PendingReturned BOOLEAN ?

    ; //
    ; // Stack state information.
    ; //

    StackCount	    CHAR ?
    CurrentLocation CHAR ?

    ; //
    ; // Cancel - packet has been canceled.
    ; //

    Cancel BOOLEAN ?

    ; //
    ; // Cancel Irql - Irql at which the cancel spinlock was acquired.
    ; //

    CancelIrql KIRQL ?

    ; //
    ; // ApcEnvironment - Used to save the APC environment at the time that the
    ; // packet was initialized.
    ; //

    ApcEnvironment CCHAR ?

    ; //
    ; // Allocation control flags.
    ; //

    AllocationFlags UCHAR ?

    ; //
    ; // User parameters.
    ; //

    UserIosb  PIO_STATUS_BLOCK ?
    UserEvent PKEVENT ?
    union ; Overlay
	struct ; AsynchronousParameters
	    Overlay.AsynchronousParameters.UserApcRoutine PIO_APC_ROUTINE ?
	    Overlay.AsynchronousParameters.UserApcContext PVOID ?
	ends ; AsynchronousParameters
	Overlay.AllocationSize LARGE_INTEGER ?
    ends ; Overlay

    ; //
    ; // CancelRoutine - Used to contain the address of a cancel routine supplied
    ; // by a device driver when the IRP is in a cancelable state.
    ; //

    CancelRoutine PDRIVER_CANCEL ?

    ; //
    ; // Note that the UserBuffer parameter is outside of the stack so that I/O
    ; // completion can copy data back into the user's address space without
    ; // having to know exactly which service was being invoked.  The length
    ; // of the copy is stored in the second half of the I/O status block. If
    ; // the UserBuffer field is NULL, then no copy is performed.
    ; //

    UserBuffer PVOID ?

    ; //
    ; // Kernel structures
    ; //
    ; // The following section contains kernel structures which the IRP needs
    ; // in order to place various work information in kernel controller system
    ; // queues.  Because the size and alignment cannot be controlled, they are
    ; // placed here at the end so they just hang off and do not affect the
    ; // alignment of other fields in the IRP.
    ; //

    union ; Tail
	struct ; Overlay
	    union
		; //
		; // DeviceQueueEntry - The device queue entry field is used to
		; // queue the IRP to the device driver device queue.
		; //

		Tail.Overlay.DeviceQueueEntry KDEVICE_QUEUE_ENTRY ?

		struct
		    ; //
		    ; // The following are available to the driver to use in
		    ; // whatever manner is desired, while the driver owns the
		    ; // packet.
		    ; //

		    Tail.Overlay.DriverContext PVOID (4) dup (?)
		ends
	    ends

	    ; //
	    ; // Thread - pointer to caller's Thread Control Block.
	    ; //

	    Tail.Overlay.Thread PETHREAD ?

	    ; //
	    ; // Auxiliary buffer - pointer to any auxiliary buffer that is
	    ; // required to pass information to a driver that is not contained
	    ; // in a normal buffer.
	    ; //

	    Tail.Overlay.AuxiliaryBuffer PCHAR ?

	    ; //
	    ; // The following unnamed structure must be exactly identical
	    ; // to the unnamed structure used in the minipacket header used
	    ; // for completion queue entries.
	    ; //

	    struct
		; //
		; // List entry - used to queue the packet to completion queue, among
		; // others.
		; //

		Tail.Overlay.ListEntry LIST_ENTRY ?

		union
		    ; //
		    ; // Current stack location - contains a pointer to the current
		    ; // IO_STACK_LOCATION structure in the IRP stack.	This field
		    ; // should never be directly accessed by drivers.	They should
		    ; // use the standard functions.
		    ; //

		    Tail.Overlay.CurrentStackLocation PVOID ? ; PIO_STACK_LOCATION ?

		    ; //
		    ; // Minipacket type.
		    ; //

		    Tail.Overlay.PacketType ULONG ?
					    PADDING 4, 0
		ends
	    ends

	    ; //
	    ; // Original file object - pointer to the original file object
	    ; // that was used to open the file.  This field is owned by the
	    ; // I/O system and should not be used by any other drivers.
	    ; //

	    Tail.Overlay.OriginalFileObject PFILE_OBJECT ?
	ends ; Overlay

	; //
	; // APC - This APC control block is used for the special kernel APC as
	; // well as for the caller's APC, if one was specified in the original
	; // argument list.  If so, then the APC is reused for the normal APC for
	; // whatever mode the caller was in and the "special" routine that is
	; // invoked before the APC gets control simply deallocates the IRP.
	; //

	Tail.Apc KAPC ?

	; //
	; // CompletionKey - This is the key that is used to distinguish
	; // individual I/O operations initiated on a single file handle.
	; //

	Tail.CompletionKey PVOID ?
    ends ; Tail
ends
VIRTDEF V_IRP, T_IRP

TYPEDEF PIO_COMPLETION_ROUTINE, PVOID

TYPEDEF DEVICE_RELATION_TYPE, enum
    BusRelations	 = 0
    EjectionRelations	 = 1
    PowerRelations	 = 2
    RemovalRelations	 = 3
    TargetDeviceRelation = 4
    SingleBusRelations	 = 5
TYPEDEF PDEVICE_RELATION_TYPE, PVOID

TYPEDEF DEVICE_USAGE_NOTIFICATION_TYPE, enum
    DeviceUsageTypeUndefined   = 0
    DeviceUsageTypePaging      = 1
    DeviceUsageTypeHibernation = 2
    DeviceUsageTypeDumpFile    = 3
TYPEDEF PDEVICE_USAGE_NOTIFICATION_TYPE, PVOID

TYPEDEF PDEVICE_CAPABILITIES, PVOID

TYPEDEF PPOWER_SEQUENCE, PVOID
struct POWER_SEQUENCE
    SequenceD1 ULONG ?
    SequenceD2 ULONG ?
    SequenceD3 ULONG ?
ends

TYPEDEF BUS_QUERY_ID_TYPE, enum
    BusQueryDeviceID	       = 0  ; // <Enumerator>\<Enumerator-specific device id>
    BusQueryHardwareIDs        = 1  ; // Hardware ids
    BusQueryCompatibleIDs      = 2  ; // compatible device ids
    BusQueryInstanceID	       = 3  ; // persistent id for this instance of the device
    BusQueryDeviceSerialNumber = 4  ; // serial number for this device
TYPEDEF PBUS_QUERY_ID_TYPE, PVOID

TYPEDEF DEVICE_TEXT_TYPE, enum
    DeviceTextDescription	  = 0	  ; // DeviceDesc property
    DeviceTextLocationInformation = 1	  ; // DeviceLocation property
TYPEDEF PDEVICE_TEXT_TYPE, PVOID

TYPEDEF PIO_STACK_LOCATION, PVOID
struct IO_STACK_LOCATION
    MajorFunction UCHAR ?
    MinorFunction UCHAR ?
    Flags	  UCHAR ?
    Control	  UCHAR ?
		  PADDING 4, 0

    ; //
    ; // The following user parameters are based on the service that is being
    ; // invoked.  Drivers and file systems can determine which set to use based
    ; // on the above major and minor function codes.
    ; //
    union ; Parameters
	; //
	; // System service parameters for:  NtCreateFile
	; //

	struct ; Create
	    Parameters.Create.SecurityContext PIO_SECURITY_CONTEXT ?
	    Parameters.Create.Options	      ULONG ?
					      PADDING 4, 0
	    Parameters.Create.FileAttributes  USHORT ? ; POINTER_ALIGNMENT ;
	    Parameters.Create.ShareAccess     USHORT ?
					      PADDING 4, 0
	    Parameters.Create.EaLength	      ULONG ? ; POINTER_ALIGNMENT ;
	ends ; Create

	; //
	; // System service parameters for:  NtReadFile
	; //

	struct ; Read
	    Parameters.Read.Length     ULONG ?
	    Parameters.Read.Key        ULONG ? ; POINTER_ALIGNMENT ;
	    Parameters.Read.ByteOffset LARGE_INTEGER ?
	ends ; Read

	; //
	; // System service parameters for:  NtWriteFile
	; //

	struct ; Write
	    Parameters.Write.Length	ULONG ?
	    Parameters.Write.Key	ULONG ? ; POINTER_ALIGNMENT ;
	    Parameters.Write.ByteOffset LARGE_INTEGER ?
	ends ; Write

	; //
	; // System service parameters for:  NtQueryInformationFile
	; //

	struct ; QueryFile
	    Parameters.QueryFile.Length 	      ULONG ?
	    Parameters.QueryFile.FileInformationClass FILE_INFORMATION_CLASS ? ; POINTER_ALIGNMENT ;
	ends ; QueryFile

	; //
	; // System service parameters for:  NtSetInformationFile
	; //

	struct ; SetFile
	    Parameters.SetFile.Length		    ULONG ?
	    Parameters.SetFile.FileInformationClass FILE_INFORMATION_CLASS ? ; POINTER_ALIGNMENT ;
	    Parameters.SetFile.FileObject	    PFILE_OBJECT ?
	    union
		struct
		    Parameters.SetFile.ReplaceIfExists BOOLEAN ?
		    Parameters.SetFile.AdvanceOnly     BOOLEAN ?
		ends
		Parameters.SetFile.ClusterCount ULONG ?
		Parameters.SetFile.DeleteHandle HANDLE ?
	    ends
	ends ; SetFile

	; //
	; // System service parameters for:  NtQueryVolumeInformationFile
	; //

	struct ; QueryVolume
	    Parameters.QueryVolume.Length	      ULONG ?
	    Parameters.QueryVolume.FsInformationClass FS_INFORMATION_CLASS ? ; POINTER_ALIGNMENT ;
	ends ; QueryVolume

	; //
	; // System service parameters for:  NtFlushBuffersFile
	; //
	; // No extra user-supplied parameters.
	; //

	; //
	; // System service parameters for:  NtDeviceIoControlFile
	; //
	; // Note that the user's output buffer is stored in the UserBuffer field
	; // and the user's input buffer is stored in the SystemBuffer field.
	; //

	struct ; DeviceIoControl
	    Parameters.DeviceIoControl.OutputBufferLength ULONG ?
	    Parameters.DeviceIoControl.InputBufferLength  ULONG ? ; POINTER_ALIGNMENT ;
	    Parameters.DeviceIoControl.IoControlCode	  ULONG ? ; POINTER_ALIGNMENT ;
	    Parameters.DeviceIoControl.Type3InputBuffer   PVOID ?
	ends ; DeviceIoControl

	; //
	; // System service parameters for:  NtQuerySecurityObject
	; //

	struct ; QuerySecurity
	    Parameters.QuerySecurity.SecurityInformation SECURITY_INFORMATION ?
	    Parameters.QuerySecurity.Length		 ULONG ? ; POINTER_ALIGNMENT ;
	ends ; QuerySecurity

	; //
	; // System service parameters for:  NtSetSecurityObject
	; //

	struct ; SetSecurity
	    Parameters.SetSecurity.SecurityInformation SECURITY_INFORMATION ?
	    Parameters.SetSecurity.SecurityDescriptor  PSECURITY_DESCRIPTOR ?
	ends ; SetSecurity

	; //
	; // Non-system service parameters.
	; //
	; // Parameters for MountVolume
	; //

	struct ; MountVolume
	    Parameters.MountVolume.Vpb		PVPB ?
	    Parameters.MountVolume.DeviceObject PDEVICE_OBJECT ?
	ends ; MountVolume

	; //
	; // Parameters for VerifyVolume
	; //

	struct ; VerifyVolume
	    Parameters.VerifyVolume.Vpb 	 PVPB ?
	    Parameters.VerifyVolume.DeviceObject PDEVICE_OBJECT ?
	ends ; VerifyVolume

	; //
	; // Parameters for Scsi with internal device contorl.
	; //

	struct ; Scsi
	    Parameters.Scsi.Srb PVOID ? ; PSCSI_REQUEST_BLOCK ?
	ends ; Scsi

	; //
	; // Parameters for IRP_MN_QUERY_DEVICE_RELATIONS
	; //

	struct ; QueryDeviceRelations
	    Parameters.QueryDeviceRelations.Type DEVICE_RELATION_TYPE ?
	ends ; QueryDeviceRelations

	; //
	; // Parameters for IRP_MN_QUERY_INTERFACE
	; //

	struct ; QueryInterface
	    Parameters.QueryInterface.InterfaceType	    PVOID ? ; PGUID ?
	    Parameters.QueryInterface.Size		    USHORT ?
	    Parameters.QueryInterface.Version		    USHORT ?
	    Parameters.QueryInterface.Interface 	    PVOID ? ; PINTERFACE ?
	    Parameters.QueryInterface.InterfaceSpecificData PVOID ?
	ends ; QueryInterface

	; //
	; // Parameters for IRP_MN_QUERY_CAPABILITIES
	; //

	struct ; DeviceCapabilities
	    Parameters.DeviceCapabilities.Capabilities PDEVICE_CAPABILITIES ?
	ends ; DeviceCapabilities

	; //
	; // Parameters for IRP_MN_FILTER_RESOURCE_REQUIREMENTS
	; //

	struct ; FilterResourceRequirements
	    Parameters.IoResourceRequirementList PIO_RESOURCE_REQUIREMENTS_LIST ?
	ends ; FilterResourceRequirements

	; //
	; // Parameters for IRP_MN_READ_CONFIG and IRP_MN_WRITE_CONFIG
	; //

	struct ; ReadWriteConfig
	    Parameters.ReadWriteConfig.WhichSpace ULONG ?
	    Parameters.ReadWriteConfig.Buffer	  PVOID ?
	    Parameters.ReadWriteConfig.Offset	  ULONG ?
	    Parameters.ReadWriteConfig.Length	  ULONG ? ; POINTER_ALIGNMENT ;
	ends ; ReadWriteConfig

	; //
	; // Parameters for IRP_MN_SET_LOCK
	; //

	struct ; SetLock
	    Parameters.SetLock.Lock BOOLEAN ?
	ends ; SetLock

	; //
	; // Parameters for IRP_MN_QUERY_ID
	; //

	struct ; QueryId
	    Parameters.QueryId.IdType BUS_QUERY_ID_TYPE ?
	ends ; QueryId

	; //
	; // Parameters for IRP_MN_QUERY_DEVICE_TEXT
	; //

	struct ; QueryDeviceText
	    Parameters.QueryDeviceText.DeviceTextType DEVICE_TEXT_TYPE ?
	    Parameters.QueryDeviceText.LocaleId       LCID ? ; POINTER_ALIGNMENT ;
	ends ; QueryDeviceText

	; //
	; // Parameters for IRP_MN_DEVICE_USAGE_NOTIFICATION
	; //

	struct ; UsageNotification
	    Parameters.UsageNotification.InPath   BOOLEAN ?
	    Parameters.UsageNotification.Reserved BOOLEAN (3) dup(?)
	    Parameters.UsageNotification.Type	  DEVICE_USAGE_NOTIFICATION_TYPE ? ; POINTER_ALIGNMENT ;
	ends ; UsageNotification

	; //
	; // Parameters for IRP_MN_WAIT_WAKE
	; //

	struct ; WaitWake
	    Parameters.WaitWake.PowerState SYSTEM_POWER_STATE ?
	ends ; WaitWake

	; //
	; // Parameter for IRP_MN_POWER_SEQUENCE
	; //

	struct ; PowerSequence
	    Parameters.PowerSequence.PowerSequence PPOWER_SEQUENCE ?
	ends ; PowerSequence

	; //
	; // Parameters for IRP_MN_SET_POWER and IRP_MN_QUERY_POWER
	; //

	struct ; Power
	    Parameters.Power.SystemContext ULONG ?
	    Parameters.Power.Type	   POWER_STATE_TYPE ? ; POINTER_ALIGNMENT ;
	    Parameters.Power.State	   POWER_STATE ? ; POINTER_ALIGNMENT ;
	    Parameters.Power.ShutdownType  POWER_ACTION ? ; POINTER_ALIGNMENT ;
	ends ; Power

	; //
	; // Parameters for StartDevice
	; //

	struct ; StartDevice
	    Parameters.StartDevice.AllocatedResources		PCM_RESOURCE_LIST ?
	    Parameters.StartDevice.AllocatedResourcesTranslated PCM_RESOURCE_LIST ?
	ends ; StartDevice

	; //
	; // Parameters for Cleanup
	; //
	; // No extra parameters supplied
	; //

	; //
	; // WMI Irps
	; //

	struct ; WMI
	    Parameters.WMI.ProviderId ULONG_PTR ?
	    Parameters.WMI.DataPath   PVOID ?
	    Parameters.WMI.BufferSize ULONG ?
	    Parameters.WMI.Buffer     PVOID ?
	ends ; WMI

	; //
	; // Others - driver-specific
	; //

	struct ; Others
	    Parameters.Others.Argument1 PVOID ?
	    Parameters.Others.Argument2 PVOID ?
	    Parameters.Others.Argument3 PVOID ?
	    Parameters.Others.Argument4 PVOID ?
	ends ; Others
    ends ; Parameters

    ; //
    ; // Save a pointer to this device driver's device object for this request
    ; // so it can be passed to the completion routine if needed.
    ; //

    DeviceObject PDEVICE_OBJECT ?

    ; //
    ; // The following location contains a pointer to the file object for this
    ; //

    FileObject PFILE_OBJECT ?

    ; //
    ; // The following routine is invoked depending on the flags in the above
    ; // flags field.
    ; //

    CompletionRoutine PIO_COMPLETION_ROUTINE ?

    ; //
    ; // The following is used to store the address of the context parameter
    ; // that should be passed to the CompletionRoutine.
    ; //

    Context PVOID ?
ends
VIRTDEF V_IO_STACK_LOCATION, IO_STACK_LOCATION

; ------------------------------------------------------------------------------
