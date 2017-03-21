
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

enum ePenStyle {
    kSolid = 0,
    kDash,
    kDot,
    kDashDot,
    kDashDotDot,
    kLast
}

enum eBrushStyle{
    kNone,
    kSolid,
}

enum eEffect {
    kNone,
    kBlur,
    kColorize,
    kShadow,
}