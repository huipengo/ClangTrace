# ClangTrace

[![CI Status](https://img.shields.io/travis/huipeng/ClangTrace.svg?style=flat)](https://travis-ci.org/huipengo/ClangTrace)
[![Version](https://img.shields.io/cocoapods/v/ClangTrace.svg?style=flat)](https://cocoapods.org/pods/ClangTrace)
[![License](https://img.shields.io/cocoapods/l/ClangTrace.svg?style=flat)](https://cocoapods.org/pods/ClangTrace)
[![Platform](https://img.shields.io/cocoapods/p/ClangTrace.svg?style=flat)](https://cocoapods.org/pods/ClangTrace)

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

## Build Settings：

在App 的 `Target` - `Build Settings` - `Other C Flags` **Debug**  增加 `-fsanitize-coverage=func,trace-pc-guard`
> OC - Swift 混编，则在 `Other Swift Flags` **Debug** 增加 `-sanitize-coverage=func` 和 `-sanitize=undefined`

---

> Cocoapods 管理代码，用的是静态库的方式的话，那么可以通过hook来修改所有的pod库的编译选项；将以下内容拷贝到你的Podfile文件下面，执行 `pod install --no-repo-update`

```ruby
post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      macho_type = config.build_settings['MACH_O_TYPE']
      #if macho_type == 'staticlib'
        # 将依赖的pod项目的Other C Flags加上’-fsanitize-coverage=func,trace-pc-guard‘选项
        config.build_settings['OTHER_CFLAGS'] ||= ['$(inherited)', '-fsanitize-coverage=func,trace-pc-guard']
        config.build_settings['OTHER_SWIFT_FLAGS'] ||= ['$(inherited)', '-fsanitize-coverage=func,trace-pc-guard']
      #end
    end
  end
end
```

## Requirements

iOS 9.0

## Installation

ClangTrace is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'ClangTrace', :git => 'https://github.com/huipengo/ClangTrace.git', :configurations => ['Debug']
```

会在 App 的沙盒的 tmp 目录下生成 `trace.order` 文件

> Xcode 的连接器 ld 默认忽略 `order file` 中 `不存在的方法`
在 `Other Linker Flags：` **Debug** 添加 `-order_file_statistics`，会以 `warning` 的形式把这些没找到的符号打印在日志里


## Author

huipeng, penghui_only@163.com

## License

ClangTrace is available under the MIT license. See the LICENSE file for more info.

## 简书

[iOS App启动优化 - 二进制重排](https://www.jianshu.com/p/f9b305e2823d)
