
#import <UIKit/UIKit.h>
#import <objc/runtime.h>

#pragma mark - 变量-AppDelegate
#define WQAPPDELEGATE ((AppDelegate*)[[UIApplication sharedApplication] delegate])

#pragma mark - weakify、strongify的宏定义

#define WeakSelf __weak __typeof(&*self)weakSelf = self

#ifndef weakify
#if DEBUG
#if __has_feature(objc_arc)
#define weakify(object) autoreleasepool{} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) autoreleasepool{} __block __typeof__(object) block##_##object = object;
#endif
#else
#if __has_feature(objc_arc)
#define weakify(object) try{} @finally{} {} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) try{} @finally{} {} __block __typeof__(object) block##_##object = object;
#endif
#endif
#endif

#ifndef strongify
#if DEBUG
#if __has_feature(objc_arc)
#define strongify(object) autoreleasepool{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) autoreleasepool{} __typeof__(object) object = block##_##object;
#endif
#else
#if __has_feature(objc_arc)
#define strongify(object) try{} @finally{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) try{} @finally{} __typeof__(object) object = block##_##object;
#endif
#endif
#endif

#pragma mark - 变量-编译相关
// 判断当前是否debug编译模式
#ifdef DEBUG
#define IS_DEBUG YES
#else
#define IS_DEBUG NO
#endif

#pragma mark - 获取项目版本号
#define CURRENT_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]

// 使用iOS8 API时要加`ifdef IOS8_SDK_ALLOWED`的判断
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
#define IOS8_SDK_ALLOWED YES
#endif

// 使用iOS9 API时要加`ifdef IOS9_SDK_ALLOWED`的判断
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 90000
#define IOS9_SDK_ALLOWED YES
#endif


// 使用iOS10 API时要加`ifdef IOS10_SDK_ALLOWED`的判断
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000
#define IOS10_SDK_ALLOWED YES
#endif

// 使用iOS11 API时要加`ifdef IOS11_SDK_ALLOWED`的判断
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 110000
#define IOS11_SDK_ALLOWED YES
#endif


#pragma mark - Clang

#define ArgumentToString(macro) #macro
#define ClangWarningConcat(warning_name) ArgumentToString(clang diagnostic ignored warning_name)

// 参数可直接传入 clang 的 warning 名，warning 列表参考：http://fuckingclangwarnings.com/
#define BeginIgnoreClangWarning(warningName) _Pragma("clang diagnostic push") _Pragma(ClangWarningConcat(#warningName))
#define EndIgnoreClangWarning _Pragma("clang diagnostic pop")

#define BeginIgnoreAvailabilityWarning BeginIgnoreClangWarning(-Wpartial-availability)
#define EndIgnoreAvailabilityWarning EndIgnoreClangWarning


#pragma mark - 变量-设备相关
#pragma mark - 操作系统版本号
#define IOS_VERSION ([[[UIDevice currentDevice] systemVersion] floatValue])

#pragma mark - 系统版本判断
#define iOS7Later   ([UIDevice currentDevice].systemVersion.floatValue >= 7.0f)
#define iOS8Later   ([UIDevice currentDevice].systemVersion.floatValue >= 8.0f)
#define iOS9Later   ([UIDevice currentDevice].systemVersion.floatValue >= 9.0f)
#define iOS10Later  ([UIDevice currentDevice].systemVersion.floatValue >= 10.0f)
#define iOS11Later  ([UIDevice currentDevice].systemVersion.floatValue >= 11.0f)
#define iOS11Before ([UIDevice currentDevice].systemVersion.floatValue < 11.0f)
#define iOS10Before ([UIDevice currentDevice].systemVersion.floatValue < 10.0f)
#define iOS9Before  ([UIDevice currentDevice].systemVersion.floatValue < 9.0f)
#define iOS8Before  ([UIDevice currentDevice].systemVersion.floatValue < 8.0f)

#pragma mark - 判断设备iPhone4
#define iPhone4s ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) : NO)

#pragma mark - 判断设备iPhone5
#define iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)

#pragma mark - 判断iphone6
#define iPhone6 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) : NO)

#pragma mark - 判断iphone6+
#define iPhone6Plus ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size) : NO)

#pragma mark - 判断iphoneX
#define iPhoneX ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125,2436), [[UIScreen mainScreen] currentMode].size) : NO)

#pragma mark - 变量-布局相关

#define Width(v)                CGRectGetWidth((v).frame)
#define Height(v)               CGRectGetHeight((v).frame)

#pragma mark - 屏幕高度、宽度
#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)

#pragma mark - 屏幕高度、宽度
#define ScreenNativeBoundsSize (IOS_VERSION >= 8.0 ? ([[UIScreen mainScreen] nativeBounds].size) : SCREEN_WIDTH)
#define ScreenScale ([[UIScreen mainScreen] scale])
#define ScreenNativeScale (IOS_VERSION >= 8.0 ? ([[UIScreen mainScreen] nativeScale]) : ScreenScale)

// 区分设备是否处于放大模式（iPhone 6及以上的设备支持放大模式）
#define ScreenInDisplayZoomMode (ScreenNativeScale > ScreenScale)

// 状态栏高度(来电等情况下，状态栏高度会发生变化，所以应该实时计算)
#define kStatusBarHeight (IOS_VERSION >= 8.0 ? ([[UIApplication sharedApplication] statusBarFrame].size.height) : (IS_LANDSCAPE ? ([[UIApplication sharedApplication] statusBarFrame].size.width) : ([[UIApplication sharedApplication] statusBarFrame].size.height)))

#define KNavgiationBarHeight CGRectGetHeight(self.navigationController.navigationBar.frame)

#define KTabBarHeight ([[UIApplication sharedApplication] statusBarFrame].size.height>20?83:49)


#pragma mark - 方法-创建器

// 使用文件名(不带后缀名)创建一个UIImage对象，会被系统缓存，适用于大量复用的小资源图
#define UIImageMake(img) \
BeginIgnoreAvailabilityWarning \
(IOS_VERSION >= 8.0 ? [UIImage imageNamed:img inBundle:nil compatibleWithTraitCollection:nil] : [UIImage imageNamed:img]) \
EndIgnoreAvailabilityWarning

// 使用文件名(不带后缀名，仅限png)创建一个UIImage对象，不会被系统缓存，用于不被复用的图片，特别是大图
#define UIImageMakeWithFile(name) UIImageMakeWithFileAndSuffix(name, @"png")
#define UIImageMakeWithFileAndSuffix(name, suffix) [UIImage imageWithContentsOfFile:[NSString stringWithFormat:@"%@/%@.%@", [[NSBundle mainBundle] resourcePath], name, suffix]]

// 字体相关创建器，包括动态字体的支持
#define UIFontMake(size) [UIFont systemFontOfSize:size]
#define UIFontItalicMake(size) [UIFont italicSystemFontOfSize:size] // 斜体只对数字和字母有效，中文无效
#define UIFontBoldMake(size) [UIFont boldSystemFontOfSize:size]
#define UIFontBoldWithFont(_font) [UIFont boldSystemFontOfSize:_font.pointSize]

// UIColor相关创建器
#define UIColorMake(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1]
#define UIColorMakeWithRGBA(r, g, b, a) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a/1.0]


// 判断字符串是否为空
#define NULLString(string) ((![string isKindOfClass:[NSString class]])||[string isEqualToString:@""] || (string == nil) || [string isEqualToString:@""] || [string isKindOfClass:[NSNull class]]||[[string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]] length]==0 || [string isEqualToString:@"(null)"])

#pragma mark - 其他

// NSLog（打印文件名、行数、具体目标）
#ifdef DEBUG
#define NSLog(FORMAT, ...) fprintf(stderr, "%s:%zd\t%s\n", [[[NSString stringWithUTF8String: __FILE__] lastPathComponent] UTF8String], __LINE__, [[NSString stringWithFormat: FORMAT, ## __VA_ARGS__] UTF8String]);
#else
#define NSLog(...)
#endif

#pragma mark - 方法-C对象、结构操作

CG_INLINE void
ReplaceMethod(Class _class, SEL _originSelector, SEL _newSelector) {
    Method oriMethod = class_getInstanceMethod(_class, _originSelector);
    Method newMethod = class_getInstanceMethod(_class, _newSelector);
    BOOL isAddedMethod = class_addMethod(_class, _originSelector, method_getImplementation(newMethod), method_getTypeEncoding(newMethod));
    if (isAddedMethod) {
        class_replaceMethod(_class, _newSelector, method_getImplementation(oriMethod), method_getTypeEncoding(oriMethod));
    } else {
        method_exchangeImplementations(oriMethod, newMethod);
    }
}

