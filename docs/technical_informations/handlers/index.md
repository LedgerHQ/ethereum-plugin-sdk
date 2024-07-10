# Handlers

Handlers are callbacks that the Ethereum application calls through the Ethereum plugin SDK to parse and display a smart contract. 

This is the list of all handlers that each plugin must define:
```c
--8<-- "src/eth_plugin_interface.h:handlers_functions"
```

Please look at the [sequence diagram](../diagram.md) to better understand at which step each handler is called.
