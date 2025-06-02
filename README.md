# Service Provider Process Data Inspection

This service provider creates services to inspect process data content via asynchronous service calls.

## Usage

To use this service provider it just has to be loaded by robotkernel in the `service_providers` section.

```yaml
service_providers:
- name: mi_sp
  so_file: libservice_provider_process_data_inspection.so
```

## Services

**in**
:   Read input data memory 

```yaml
name: service_provider/process_data_inspection/in
response:
- vector/uint8_t: data
- string: error_message
```

**out**
:   Read outpout data memory

```yaml
name: service_provider/process_data_inspection/out
response:
- vector/uint8_t: data
- string: error_message
```

## Implementation specific

Either use conan to add the needed include and library pathes to you project or use pkg-config with the 
provided pkc-file.

First thing to do is to include the base header:

```c
#include "service_provider/process_data_inspection/base.h"

```

After this you have to dervive a class from the `service_provider::process_data_inspection::base` class 
and implement the corresponding process data inspection functions.

```c
class my_class : public service_provider::process_data_inspection::base {
    public:
        my_class() { /* init things here */ }

        //! return input process data (measurements)
        /*!
         * \param pd return input process data
         */
        virtual void get_pdin(pd_t& pd) { /* fill pd struct here */ }

        //! return output process data (commands)
        /*!
         * \param pd return output process data
         */
        virtual void get_pdout(pd_t& pd) { /* fill pd struct here */ }
};
```

