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
    void MainWindow::OpenFolderPage_Click(Windows::Foundation::IInspectable const& /*sender*/, Microsoft::UI::Xaml::RoutedEventArgs const& /*args*/)
    {
        // Navigate to folder monitoring page using the main content frame
        // xaml_typename<> ensures type safety and proper runtime type resolution
        contentFrame().Navigate(xaml_typename<WindowsNativeToolkit::FolderMonitorPage>());
    }
}
