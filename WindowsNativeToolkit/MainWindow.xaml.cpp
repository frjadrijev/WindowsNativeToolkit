#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
/// <summary>
/// Auto-generated implementation support for MainWindow.
/// Provides factory methods, XAML loading infrastructure, and activation support.
/// </summary>
#include "MainWindow.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WindowsNativeToolkit::implementation
{
    /// <summary>
    /// Handles the "Open folder page" button click event.
    /// Performs navigation to the FolderMonitorPage using the WinUI Frame navigation system.
    /// </summary>
    /// <param name="sender">Button control that triggered the event (marked unused)</param>
    /// <param name="args">Routed event arguments (marked unused)</param>
    /// <remarks>
    /// Implementation details:
    /// 
    /// Navigation mechanism:
    /// - Uses contentFrame() to access the named Frame element from XAML
    /// - Calls Navigate() with xaml_typename for type-safe navigation
    /// - xaml_typename<> provides compile-time type checking and runtime type info
    /// 
    /// Page lifecycle:
    /// - FolderMonitorPage is instantiated during navigation
    /// - Page constructor and Initialize() methods are called automatically
    /// - Previous page state is maintained by Frame navigation history
    /// 
    /// Error handling:
    /// - Frame.Navigate() handles navigation failures internally
    /// - Type safety is guaranteed by xaml_typename template
    /// - Invalid navigation attempts result in no operation (fail-safe)
    /// 
    /// Performance characteristics:
    /// - Navigation is synchronous and completes immediately
    /// - Page creation overhead is minimal for lightweight pages
    /// - Frame control manages page lifecycle and memory automatically
    /// 
    /// Threading:
    /// - Executes on UI thread (required for XAML operations)
    /// - Event handler is automatically marshaled to UI thread by WinUI
    /// - No additional synchronization required
    /// 
    /// Future extensions:
    /// - Could pass navigation parameters via Navigate() overloads
    /// - Could implement navigation guards or user confirmation
    /// - Could add navigation analytics or telemetry
    /// - Could support deep linking or external navigation requests
    /// </remarks>
    void MainWindow::OpenFolderPage_Click(Windows::Foundation::IInspectable const& /*sender*/, Microsoft::UI::Xaml::RoutedEventArgs const& /*args*/)
    {
        // Navigate to the folder monitoring page using the main content frame
        // 
        // <Frame x:Name="contentFrame"/> in MainWindow.xaml provides the navigation host
        // xaml_typename<> ensures type safety and proper runtime type resolution
        contentFrame().Navigate(xaml_typename<WindowsNativeToolkit::FolderMonitorPage>());
    }
}
