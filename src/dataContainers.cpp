#include "dataContainer.h"

IDataContainer* CreateContainer(DataType type) {
    switch (type) {
        case DT_INT8:   
          return new ValueContainer<int8_t>(type);
        case DT_UINT8:  
          return new ValueContainer<uint8_t>(type);
        case DT_INT16:  
          return new ValueContainer<int16_t>(type);
        case DT_UINT16: 
          return new ValueContainer<uint16_t>(type);
        case DT_INT32:  
          return new ValueContainer<int32_t>(type);
        case DT_UINT32: 
          return new ValueContainer<uint32_t>(type);
        case DT_INT64:  
          return new ValueContainer<int64_t>(type);
        case DT_UINT64: 
          return new ValueContainer<uint64_t>(type);
        case DT_STRING: 
          return new StrContainer(DT_STRING); 
        case DT_CHAR:
          return new ValueContainer<char>(type);
        default:        
          return new StrContainer(DT_STRING);
    }
}
