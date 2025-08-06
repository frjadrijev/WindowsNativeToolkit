#pragma once

#include "FolderMonitorPage.g.h"
#include <FolderMonitorPageViewModel.h>

namespace winrt::WindowsNativeToolkit::implementation
{
    /// <summary>
    /// Implementation class for the FolderMonitorPage Windows Runtime component.
    /// Provides the user interface for file system monitoring functionality with
    /// integrated ViewModel support following MVVM architectural patterns.
    /// </summary>
    /// <remarks>
    /// This class serves as the View component in the Model-View-ViewModel pattern,
    /// providing the user interface layer for file system monitoring functionality.
    /// It demonstrates modern WinUI development patterns including:
    /// 
    /// MVVM Integration:
    /// - Maintains reference to associated ViewModel
    /// - Sets DataContext for XAML data binding
    /// - Separates UI logic from business logic
    /// - Enables testable and maintainable code architecture
    /// 
    /// Page lifecycle:
    /// - Constructor performs minimal setup
    /// - Initialize() method handles ViewModel creation and binding
    /// - XAML loading deferred per WinUI best practices
    /// - Automatic cleanup when page is navigated away
    /// 
    /// Data binding:
    /// - Uses compiled binding (x:DataType) for performance
    /// - Automatic UI updates via PropertyChanged notifications
    /// - Type-safe property access with compile-time verification
    /// - Support for complex data scenarios and collections
    /// 
    /// Threading considerations:
    /// - UI operations execute on main thread
    /// - ViewModel operations may involve background threads
    /// - Automatic marshaling for PropertyChanged events
    /// - Thread-safe ViewModel updates through dispatcher
    /// 
    /// Performance characteristics:
    /// - Lightweight View with logic delegated to ViewModel
    /// - Efficient data binding with compiled expressions
    /// - Minimal UI thread blocking through proper async patterns
    /// - Memory-efficient through proper disposal patterns
    /// </remarks>
    struct FolderMonitorPage : FolderMonitorPageT<FolderMonitorPage>
    {
        /// <summary>
        /// Constructor for FolderMonitorPage.
        /// Performs initialization following WinUI best practices for XAML pages.
        /// </summary>
        /// <remarks>
        /// Construction sequence:
        /// 1. Base class construction (FolderMonitorPageT)
        /// 2. Initialize() call for ViewModel setup
        /// 3. XAML loading deferred until after construction
        /// 
        /// This pattern ensures proper COM activation and prevents issues
        /// that can occur when XAML elements access parent objects during
        /// construction. The Initialize() method handles ViewModel creation
        /// and DataContext binding after construction is complete.
        /// 
        /// See WinUI documentation for details on XAML construction patterns:
        /// https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        /// </remarks>
        FolderMonitorPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            Initialize();
        }

        /// <summary>
        /// Gets the ViewModel associated with this page.
        /// Provides access to the business logic and data for this view.
        /// </summary>
        /// <returns>
        /// The FolderMonitorPageViewModel instance containing the business logic
        /// and data properties for this page. Returns null if not initialized.
        /// </returns>
        /// <remarks>
        /// ViewModel access patterns:
        /// - Used by external callers to configure page behavior
        /// - Enables dependency injection and testability scenarios
        /// - Provides access to ViewModel methods and properties
        /// - Supports navigation parameter passing and state management
        /// 
        /// The noexcept specification indicates this method will not throw
        /// exceptions and is safe for use in performance-critical scenarios.
        /// 
        /// Thread safety:
        /// - Safe to call from UI thread (typical usage)
        /// - ViewModel itself may have thread-safe operations
        /// - Property access should follow ViewModel threading guidelines
        /// 
        /// Lifetime management:
        /// - ViewModel lifetime tied to page lifetime
        /// - Automatic cleanup when page is disposed
        /// - WinRT reference counting ensures proper memory management
        /// </remarks>
        WindowsNativeToolkit::FolderMonitorPageViewModel ViewModel() const noexcept;

    private:
        /// <summary>
        /// Initializes the page and sets up ViewModel integration.
        /// Called from constructor to establish data binding and business logic.
        /// </summary>
        /// <remarks>
        /// Initialization responsibilities:
        /// - Creates the ViewModel instance
        /// - Sets the page's DataContext for XAML binding
        /// - Configures any initial state or subscriptions
        /// - Prepares page for user interaction
        /// 
        /// This method is called during construction but after base class
        /// initialization is complete, ensuring safe access to all page
        /// infrastructure.
        /// </remarks>
        void Initialize(); 

        /// <summary>
        /// The ViewModel instance providing business logic and data for this page.
        /// Initialized during page construction and bound to DataContext for XAML access.
        /// </summary>
        /// <remarks>
        /// Storage details:
        /// - Uses WinRT smart pointer for automatic memory management
        /// - Initialized to nullptr until Initialize() is called
        /// - Lifetime tied to page instance lifecycle
        /// - Thread-safe access through WinRT reference counting
        /// 
        /// MVVM integration:
        /// - Serves as the Model and business logic layer
        /// - Exposes properties for XAML data binding
        /// - Handles file system monitoring operations
        /// - Provides PropertyChanged notifications for UI updates
        /// </remarks>
        WindowsNativeToolkit::FolderMonitorPageViewModel m_vm{ nullptr };
    };
}

namespace winrt::WindowsNativeToolkit::factory_implementation
{
    /// <summary>
    /// Factory implementation for creating FolderMonitorPage instances.
    /// Provides WinRT activation factory infrastructure for the page component.
    /// </summary>
    /// <remarks>
    /// This factory enables:
    /// - WinRT activation factory support
    /// - XAML instantiation via x:Class attribute
    /// - Navigation system integration
    /// - Runtime type resolution and activation
    /// 
    /// The factory is automatically registered during module initialization
    /// and handles instance creation for navigation and direct activation scenarios.
    /// </remarks>
    struct FolderMonitorPage : FolderMonitorPageT<FolderMonitorPage, implementation::FolderMonitorPage>
    {
    };
}
