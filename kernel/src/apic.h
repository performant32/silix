#ifndef APIC_H
#define APIC_H

#include "acpi.h"

static const char madt_header[4] = "MADT";

typedef struct madt_entry_t{
    uint8_t type;
    uint8_t length;
}__attribute__((packed)) madt_entry_t;

enum apic_type_t{
    PROCESSOR_LOCAL_APIC=0,
    IO_APIC,
    IO_APIC_INTERRUPT_SOURCE_OVERRIDE,
    IO_APIC_NON_MASKABLE_INTERRUPT_SOURCE,
    LOCAL_APIC_NON_MASKABLE_INTERRUPTS,
    LOCAL_APIC_ADDRESS_OVERRIDE,

    UNUSED1,
    UNUSED2,
    UNUSED3,

    PROCESSOR_LOCAL_X2APIC,
};

enum apic_polarity_e{
    APIC_PM_NO_OVERRIDE=0,
    APIC_PM_ACTIVE_HIGH_OVERRIDE,
    APIC_PM_RESERVED,
    APIC_PM_ACTIVE_LOW_OVERRIDE
};

enum apic_trigger_mode_e{
    APIC_TM_NO_OVERRIDE,
    APIC_TM_EDGE_TRIGGERED,
    APIC_TM_RESERVED,
    APIC_TM_LEVEL_TRIGGERED
};


typedef struct local_apic_t{
    madt_entry_t header;
    uint8_t processor_id;
    uint8_t id;
    uint32_t flags;
}__attribute__((packed)) local_apic_t;

typedef struct io_apic_t{
    madt_entry_t header;
    uint8_t id;
    uint8_t reserved;
    uint32_t address;
    uint32_t global_interrupt_base;
}__attribute__((packed)) io_apic_t;

typedef struct io_apic_nmis_t{
    madt_entry_t header;
    uint8_t nmi_source;
    uint8_t reserved;
    uint16_t flags;
    uint32_t global_system_interrupt;
}__attribute__((packed)) io_apic_nmis_t;

typedef struct local_apic_nmis_t{
    madt_entry_t header;
    uint8_t processor_id;
    uint16_t flags;
    uint8_t lint;
}__attribute__((packed)) local_apic_nmis_t;

typedef struct local_apic_nmi_t{
    madt_entry_t header;
    uint8_t id;// 0XFF means all processors
    uint16_t flags;
    uint8_t lint;
}__attribute__((packed)) local_apic_nmi_t;

typedef struct processor_local_x2apic_t{
    madt_entry_t header;
    uint16_t reserved;
    uint32_t processor_local_x2apic_t;
    uint32_t flags;
    uint32_t acpi_id;
}__attribute__((packed)) processor_local_x2apic_t;

typedef struct madt_t{
    sdt_header_t header;
    uint32_t local_apic_address;
    uint32_t flags;
    madt_entry_t entries[];
}__attribute__((packed)) madt_t;

typedef struct generic_address_structure_t{
    uint8_t address_space;
    uint8_t bit_width;
    uint8_t bit_offset;
    uint8_t access_size;
    uint64_t address;
}__attribute__((packed)) generic_address_structure_t;

enum address_space_e{
    SYSTEM_MEMORY=0,
    SYSTEM_IO,
    PCI_CONFIGURATION_SPACE,
    EMBEDDED_CONTROLLER,
    SYSTEM_MANAGEMENT_BUS,
    SYSTEM_CMOS,
    PCI_DEVICE_BAR_TARGET,
    INTELLIGENT_PLATFORM_MANAGEMENT_INFRASTRUCTURE,
    GENERAL_PURPOSE_IO,
    GENERIC_SERIAL_BUS,
    PLATFORM_COMMUNICATION_CHANNEL,
    //0x0b to 0x7F Reserved
    //0x80 to 0xFF
};

typedef struct fadt_t{
    sdt_header_t header;
    uint32_t firmware_ctrl;
    uint32_t dsdt;

    //compatibility field
    uint8_t reserved;

    uint8_t preferred_power_management_profile;
    uint16_t sci_interrupt;
    uint32_t smi_command_port;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t s4bios_req;
    uint8_t pstate_control;
    uint32_t pm1a_event_block;
    uint32_t pm1b_event_block;
    uint32_t pm1a_controll_block;
    uint32_t pm1b_controll_block;

    uint32_t pm2_control_block;
    uint32_t pm_timer_block;
    uint32_t gpe0_block;
    uint32_t gpe1_block;

    uint8_t pm1_event_length;
    uint8_t pm1_control_length;

    uint8_t pm1_timer_length;
    uint8_t pm2_control_length;
    uint8_t pm_timer_length;
    uint8_t gpe0_length;
    uint8_t gpe1_length;
    uint8_t gp1_base;
    uint8_t c_state_control;

    uint16_t worst_c2_latency;
    uint16_t worst_c3_latency;

    uint16_t flush_size;
    uint16_t flush_stride;

    uint8_t duty_offset;
    uint8_t duty_width;
    uint8_t day_alarm;
    uint8_t month_alarm;
    uint8_t century;

    // reserved in 1.0
    uint16_t boot_architecture_flags;

    uint8_t reserved_2;
    uint32_t flags;

    generic_address_structure_t reset_reg;
    uint8_t reset_value;
    uint8_t reserved3[3];

    uint64_t x_firmware_control;
    uint64_t x_dsdt;

    generic_address_structure_t x_pm1a_event_block;
    generic_address_structure_t x_pm1b_event_block;
    generic_address_structure_t x_pm1a_control_block;
    generic_address_structure_t x_pm1b_control_block;
    generic_address_structure_t x_pm2_control_block;
    generic_address_structure_t x_pm_timer_block;
    generic_address_structure_t x_gpe0_block;
    generic_address_structure_t x_gpe1_block;
}fadt_t;

static uint32_t* apic_registers_base = (uint32_t*)0xFEE00000;
void apic_init();

#endif
