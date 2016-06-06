
enum msgStatus { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

enum objState {
    kClean,
    kNewObject = 1,
    kModified = 2,
    kSubModified = 4,
    kMasterModified = 8, 
}

enum penStyle {
    solid,
    dash,
    dot,
    dashDot,
    dashDotDot,
}