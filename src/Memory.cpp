#include "Memory.h"

MemoryConfig_t          g_devMemoryConfig[3];




void   MemoryInit ()
{

    g_devMemoryConfig[TAG_DEVICE]        = {0x3C, 0xE9, 0x0E, 0x0B, 0x66, 0x5C}; 
    g_devMemoryConfig[ANCHOR_DEVICE_ONE] = {0xB4, 0x8A, 0x0A, 0x5D, 0x0D, 0x54}; 
    g_devMemoryConfig[ANCHOR_DEVICE_TWO] = {0x40, 0x22, 0xD8, 0x6B, 0x4C, 0x68};  

} 