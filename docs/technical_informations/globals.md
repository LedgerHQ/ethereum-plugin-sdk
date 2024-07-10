!!! warning
    Global variables should **never** be used in your plugin. Only the semi-persistent context provided by the Ethereum application should be used.

Each call by the Ethereum application starts the plugin anew with a fresh main call: everything not saved in the context is lost.

In order to retain knowledge from a handler call to another, the plugin can use a memory section allocated by the Ethereum application.

The context can be accessed through the `uint8_t *pluginContext` field of the parameter. All handlers will pass it to your plugin and it's common to your plugin's lifetime from the init call to the display.

The ethereum application will never modify the content of the structure.

This is the size available for the context of your plugin:
```c
--8<-- "src/eth_plugin_interface.h:plugin_context"
```
