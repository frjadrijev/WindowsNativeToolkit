#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WindowsNativeToolkit::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    // Add this method definition to your MainWindow implementation file
    void MainWindow::myButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        // TODO: Add your button click logic here
    }
}
