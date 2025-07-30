#include "pch.h"
#include "FolderMonitorPage.xaml.h"
#if __has_include("FolderMonitorPage.g.cpp")
#include "FolderMonitorPage.g.cpp"
#endif
#include <winrt/WindowsNativeToolkit.h> 

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WindowsNativeToolkit::implementation
{
    void FolderMonitorPage::Initialize()
    {
        m_vm = make<FolderMonitorPageViewModel>();
        DataContext(m_vm);                     // FrameworkElement::DataContext
    }

    WindowsNativeToolkit::FolderMonitorPageViewModel FolderMonitorPage::ViewModel() const noexcept 
    { 
        return m_vm; 
    }
}
