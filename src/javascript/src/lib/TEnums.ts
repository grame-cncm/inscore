
enum eMsgStatus { 
    kBadAddress = 0,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

enum eObjState {
    kClean = 0,
    kNewObject = 1,
    kModified = 2,
    kSubModified = 4,
    kMasterModified = 8, 
}

enum ePenStyle  	{ kSolid, kDash, kDot, kDashDot, kDashDotDot, kLast }
enum eBrushStyle	{ kNone, kSolid,}
enum eEffect 		{ kNone, kBlur, kColorize,kShadow, }

// WARNING: changing the enum order requires to change IEventAble too
enum eUIEvents { 
    kMouseDown = 1,
	kMouseMove = 2,
	kMouseUp  = 4,
	kMouseEnter= 8,
	kMouseLeave= 16,
	kDoubleClick= 32,
	kTouchBegin = 64,
	kTouchEnd	= 128,
	kTouchUpdate= 256
}
