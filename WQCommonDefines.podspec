
Pod::Spec.new do |s|

s.name         = "WQCommonDefines"
s.version      = "0.0.2"
s.summary      = "iOS所有项目通用的宏定义，欢迎使用和添加"
s.description  = <<-DESC
                 自己总结的通用的宏定义的Pod库，欢迎使用和添加。
                 DESC
s.homepage     = "https://github.com/WQiOS/WQCommonDefines"
s.license      = "MIT"
s.author             = { "王强" => "1570375769@qq.com" }
s.platform     = :ios, "8.0" #平台及支持的最低版本
s.requires_arc = true # 是否启用ARC
s.source       = { :git => "https://github.com/WQiOS/WQCommonDefines.git", :tag => "#{s.version}" }
s.source_files  = "WQCommonDefines/*.{h,m}"
s.ios.framework  = 'UIKit'

end
