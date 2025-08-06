#pragma once

#include "FolderMonitorPageViewModel.g.h"
#include <winrt/ToolkitCore.h>   // only include the projection
//#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>

namespace winrt::WindowsNativeToolkit::implementation
{
    /// <summary>
    /// Implementation class for the FolderMonitorPageViewModel Windows Runtime component.
    /// Provides the business logic and data binding support for file system monitoring
    /// functionality following the Model-View-ViewModel (MVVM) architectural pattern.
    /// </summary>
    /// <remarks>
    /// This class serves as the ViewModel component in the MVVM pattern, encapsulating
    /// business logic and providing a clean, testable interface between the UI and
    /// the underlying file system monitoring services.
    /// 
    /// Architecture responsibilities:
    /// - Manages folder path state and validation
    /// - Coordinates with ToolkitCore file monitoring services
    /// - Provides PropertyChanged notifications for data binding
    /// - Handles asynchronous file system events and updates
    /// - Maintains clean separation between UI and business logic
    /// 
    /// Data binding integration:
    /// - Implements INotifyPropertyChanged through [bindable] IDL attribute
    /// - Supports compiled binding (x:DataType) for performance
    /// - Provides thread-safe property updates with UI marshaling
    /// - Enables reactive UI updates based on business logic changes
    /// 
    /// Service integration:
    /// - Uses ToolkitCore.FileWatcherService for actual monitoring
    /// - Translates low-level file events to high-level UI concepts
    /// - Manages service lifecycle and resource cleanup
    /// - Provides error handling and user-friendly status updates
    /// 
    /// Threading model:
    /// - Property access is UI-thread safe
    /// - File system events handled on background threads
    /// - PropertyChanged events automatically marshaled to UI thread
    /// - Weak reference patterns prevent circular references
    /// 
    /// Memory management:
    /// - Uses WinRT reference counting for automatic cleanup
    /// - Weak references for event handlers prevent memory leaks
    /// - Service resources properly disposed when ViewModel is destroyed
    /// - Thread-safe cleanup coordination
    /// </remarks>
    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel>
    {
        /// <summary>
        /// Constructor for FolderMonitorPageViewModel.
        /// Initializes the ViewModel and sets up file monitoring service integration.
        /// </summary>
        /// <remarks>
        /// Construction sequence:
        /// 1. Base class initialization (auto-generated)
        /// 2. Initialize() call for service setup
        /// 3. Property initialization with default values
        /// 4. Event subscription setup
        /// 
        /// The constructor performs minimal work to ensure fast activation
        /// and defers heavy initialization to the Initialize() method.
        /// This pattern prevents blocking during view creation.
        /// </remarks>
        FolderMonitorPageViewModel()
        {
            Initialize();
        };
     
        /// <summary>
        /// Gets the current folder path being monitored.
        /// </summary>
        /// <returns>
        /// String containing the full path to the monitored folder.
        /// Empty string if no folder is currently being monitored.
        /// </returns>
        /// <remarks>
        /// This property getter provides access to the current folder path
        /// for data binding and programmatic access. The value is maintained
        /// internally and reflects the currently monitored location.
        /// 
        /// Thread safety:
        /// - Safe to call from UI thread (typical usage)
        /// - Value access is atomic through hstring implementation
        /// - No synchronization required for read operations
        /// </remarks>
        hstring FolderPath() const;

        /// <summary>
        /// Sets the folder path to monitor and updates associated UI bindings.
        /// </summary>
        /// <param name="path">
        /// Full path to the folder to monitor. Should be a valid, accessible
        /// directory path. Empty string to stop monitoring.
        /// </param>
        /// <remarks>
        /// Property setter responsibilities:
        /// - Updates internal folder path state
        /// - Fires PropertyChanged event for UI binding updates
        /// - Validates path accessibility and format
        /// - May trigger file monitoring service reconfiguration
        /// 
        /// Data binding integration:
        /// - Supports two-way binding for user input scenarios
        /// - Automatic UI updates through PropertyChanged events
        /// - Thread-safe updates with proper UI marshaling
        /// 
        /// Validation:
        /// - Accepts empty strings to disable monitoring
        /// - Should validate directory existence and accessibility
        /// - Consider user-friendly error reporting for invalid paths
        /// 
        /// Performance considerations:
        /// - Avoids unnecessary PropertyChanged events for same values
        /// - Defers expensive operations (service reconfiguration) if needed
        /// - Maintains responsive UI during path changes
        /// </remarks>
        void FolderPath(hstring const& path);

    private:
        /// <summary>
        /// Initializes the ViewModel and sets up file monitoring service integration.
        /// Called during construction to establish service connections and initial state.
        /// </summary>
        /// <remarks>
        /// Initialization responsibilities:
        /// - Creates and configures FileWatcherService instance
        /// - Sets up event handlers for file change notifications
        /// - Establishes initial property values and demo data
        /// - Configures weak reference patterns for memory safety
        /// 
        /// Event handling setup:
        /// - Uses weak references to prevent circular references
        /// - Ensures proper cleanup when ViewModel is destroyed
        /// - Provides thread-safe event handling with UI marshaling
        /// 
        /// This method is called once during construction and should not
        /// be called again during the ViewModel lifetime.
        /// </remarks>
        void Initialize();

        /// <summary>
        /// Raises PropertyChanged event for the specified property name.
        /// Notifies the UI binding system that a property value has changed.
        /// </summary>
        /// <param name="name">
        /// Name of the property that changed. Must match the property name
        /// used in XAML bindings for proper update notifications.
        /// </param>
        /// <remarks>
        /// PropertyChanged event handling:
        /// - Checks for valid event handler before invoking
        /// - Thread-safe event firing with automatic UI marshaling
        /// - Standard INotifyPropertyChanged pattern implementation
        /// - Enables reactive UI updates based on property changes
        /// 
        /// Usage pattern:
        /// Called from property setters after updating the backing field
        /// to notify bound UI elements that they should refresh their
        /// displayed values.
        /// 
        /// Performance considerations:
        /// - Event is only fired if handlers are registered
        /// - Uses efficient property name passing (no reflection)
        /// - Minimal overhead for unbound properties
        /// </remarks>
        void RaisePropertyChanged(hstring const& name);

        /// <summary>
        /// File monitoring service instance for detecting file system changes.
        /// Provides integration with ToolkitCore monitoring infrastructure.
        /// </summary>
        /// <remarks>
        /// Service characteristics:
        /// - Created during Initialize() method execution
        /// - Configured with appropriate event handlers
        /// - Lifecycle managed by ViewModel instance
        /// - Thread-safe operations through service implementation
        /// 
        /// Integration pattern:
        /// - Service events are translated to ViewModel property updates
        /// - Weak reference pattern prevents circular references
        /// - Automatic cleanup when ViewModel is disposed
        /// - Error handling and user-friendly status reporting
        /// </remarks>
        ToolkitCore::FileWatcherService m_fileWatcherService;

        /// <summary>
        /// Internal storage for the current folder path being monitored.
        /// Backing field for the FolderPath property with data binding support.
        /// </summary>
        /// <remarks>
        /// Storage details:
        /// - Uses WinRT hstring for efficient string handling
        /// - Maintains current folder path state
        /// - Updated through FolderPath property setter
        /// - Thread-safe access through hstring implementation
        /// 
        /// The backing field pattern separates storage from property
        /// interface, enabling validation, change detection, and
        /// event firing in the property setter.
        /// </remarks>
        winrt::hstring m_folder;   

        /// <summary>
        /// PropertyChanged event handler for data binding notifications.
        /// Auto-generated field created by [bindable] IDL attribute.
        /// </summary>
        /// <remarks>
        /// Event details:
        /// - Generated automatically by MIDL compiler from [bindable] attribute
        /// - Implements INotifyPropertyChanged pattern for data binding
        /// - Thread-safe event handler management
        /// - Automatic UI thread marshaling for event delivery
        /// 
        /// Usage:
        /// - UI bindings automatically subscribe to this event
        /// - RaisePropertyChanged() method fires this event
        /// - Enables reactive UI updates when properties change
        /// - Standard WinRT property change notification pattern
        /// </remarks>
        Microsoft::UI::Xaml::Data::PropertyChangedEventHandler m_propertyChanged;
    };
}

namespace winrt::WindowsNativeToolkit::factory_implementation
{
    /// <summary>
    /// Factory implementation for creating FolderMonitorPageViewModel instances.
    /// Provides WinRT activation factory infrastructure for the ViewModel component.
    /// </summary>
    /// <remarks>
    /// Factory capabilities:
    /// - WinRT activation factory support for ViewModel creation
    /// - Integration with dependency injection frameworks
    /// - Support for parameterized construction scenarios
    /// - Runtime type resolution and activation
    /// 
    /// The factory enables creation of ViewModel instances through:
    /// - Direct programmatic creation via winrt::make
    /// - Dependency injection container integration
    /// - XAML data context assignment scenarios
    /// - Testing and mocking infrastructure
    /// 
    /// This factory is automatically registered during module initialization
    /// and provides the foundation for all ViewModel instance creation.
    /// </remarks>
    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel, implementation::FolderMonitorPageViewModel>
    {
    };
}   