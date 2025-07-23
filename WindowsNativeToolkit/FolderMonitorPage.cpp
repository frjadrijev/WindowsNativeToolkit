#include "pch.h"  
#include "FolderMonitorPage.h"  
#if __has_include("FolderMonitorPage.g.cpp")  
#include "FolderMonitorPage.g.cpp"  
#endif  

namespace winrt::WindowsNativeToolkit::implementation
{
    int32_t FolderMonitorPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void FolderMonitorPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void FolderMonitorPage::ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        if (auto button = sender.try_as<Windows::UI::Xaml::Controls::Button>())
        {
            button.Content(box_value(L"Clicked"));
        }
        else
        {
            throw hresult_invalid_argument(L"sender must be a Button");
        }
    }
}



