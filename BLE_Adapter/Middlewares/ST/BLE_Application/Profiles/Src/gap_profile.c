/******************** (C) COPYRIGHT 2020 STMicroelectronics ********************
* File Name          : gap_profile.c
* Author             : SRA - BLE stack team
* Description        : Generic Access Profile Service (GAP)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include "gap_profile.h"
#include <string.h>
#include "osal.h"
#include "bluenrg_lp_gap.h"
#include "bluenrg_lp_api.h"
/******************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************/
/**
 * Default device name.
 */
static const uint8_t default_dev_name[] = { 'B', 'l', 'u', 'e', 'N', 'R', 'G' };

/**
 *@defgroup Device Name Characteristic value.
 *@{
 */
/**
 * Characteristic value buffer.
 */
static uint8_t gap_device_name_buff[GAP_CHR_DEVICE_NAME_VAL_LEN_MAX];

static ble_gatt_val_buffer_def_t gap_device_name_val_buff = {
    .buffer_len = GAP_CHR_DEVICE_NAME_VAL_LEN_MAX,
    .op_flags = BLE_GATT_SRV_OP_VALUE_VAR_LENGTH_FLAG | BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG,
    .buffer_p = gap_device_name_buff,
};
/**
 *@}
 */

/**
 *@defgroup Appearance Characteristic value.
 *@{
 */
/**
 * Characteristic value buffer.
 */
static uint8_t gap_appearance_buff[GAP_CHR_APPEARANCE_VAL_LEN];

static const ble_gatt_val_buffer_def_t gap_appearance_val_buff = {
    .buffer_len = GAP_CHR_APPEARANCE_VAL_LEN,
    .buffer_p = gap_appearance_buff,
};
/**
 *@}
 */

/**
 *@defgroup Peripheral Preferred Connection Parameters Characteristic value.
 *@{
 */
/**
 * Characteristic value buffer.
 */
static uint8_t gap_peripheral_preferred_con_params_buff[GAP_CHR_PERIPH_PREF_CONN_PARAMS_LEN] = {
    0xFFU, 0xFFU, 0xFFU, 0xFFU,
    0x00U, 0x00U, 0xFFU, 0xFFU
};
static const ble_gatt_val_buffer_def_t gap_peripheral_preferred_con_params_val_buff = {
    .buffer_len = GAP_CHR_PERIPH_PREF_CONN_PARAMS_LEN,
    .buffer_p = gap_peripheral_preferred_con_params_buff,
};
/**
 *@}
 */

/**
 *@defgroup Central Address Resolution Characteristic value.
 *@{
 */
/**
 * Characteristic value buffer.
 */
static uint8_t gap_central_address_resolution_buff[GAP_CHR_CENTRAL_ADDR_RESOLUTION_LEN] = { 1U };
static const ble_gatt_val_buffer_def_t gap_central_address_resolution_val_buff = {
    .buffer_len = GAP_CHR_CENTRAL_ADDR_RESOLUTION_LEN,
    .buffer_p = gap_central_address_resolution_buff,
};
/**
 *@}
 */

static ble_gatt_chr_def_t gap_chrs[] = {
    { /**< Device Name Characteristic. */
        .properties = BLE_GATT_SRV_CHAR_PROP_READ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_DEVICE_NAME_CHR_UUID),
        .min_key_size = 7U,
        .val_buffer_p = (ble_gatt_val_buffer_def_t *)&gap_device_name_val_buff,
    }, { /**< Appearance Characteristic. */
        .properties = BLE_GATT_SRV_CHAR_PROP_READ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_APPEARANCE_CHR_UUID),
        .min_key_size = 7U,
        .val_buffer_p = (ble_gatt_val_buffer_def_t *)&gap_appearance_val_buff,
    }, { /**< Peripheral Preferred Connection Parameters Characteristic. */
        .properties = BLE_GATT_SRV_CHAR_PROP_READ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_PERIPHERAL_PREFERRED_CONN_PARAMS_UUID),
        .min_key_size = 7U,
        .val_buffer_p = (ble_gatt_val_buffer_def_t *)&gap_peripheral_preferred_con_params_val_buff,
    }, { /**< Central Address Resolution Characteristic. */
        .properties = BLE_GATT_SRV_CHAR_PROP_READ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = 7U,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_CENTRAL_ADDRESS_RESOLUTION_UUID),
        .val_buffer_p = (ble_gatt_val_buffer_def_t *)&gap_central_address_resolution_val_buff,
    }
};

static ble_gatt_srv_def_t gap_srvc = {
    .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
    .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_GAP_SERVICE_UUID),
    .chrs = {
        .chrs_p = gap_chrs,
        .chr_count = 2U,
    },
};

tBleStatus Gap_profile_init(uint8_t role, uint8_t privacy_type,
                            uint8_t device_name_max_len)
{
    tBleStatus ret;
    uint16_t gap_srvc_handle;

    /**
     * Register GAP service.
     * Device Name and Appearance Characteristics will be also registered.
     */
    ret = aci_gatt_srv_add_service(&gap_srvc);
    if (ret != BLE_STATUS_SUCCESS)
    {
        return ret;
    }

    gap_srvc_handle = aci_gatt_srv_get_service_handle(&gap_srvc);
    if ((role & (GAP_PERIPHERAL_ROLE | GAP_BROADCASTER_ROLE)) != 0x0U)
    {
        /**
         * Register Peripheral Preferred Connection Parameters Characteristic.
         */
        ret = aci_gatt_srv_add_char(&gap_chrs[2U], gap_srvc_handle);
        if (ret != BLE_STATUS_SUCCESS)
        {
            return ret;
        }
    }

    if (privacy_type == 2U)
    {
        /**
         * Register Central Address Resolution Characteristic.
         */
        ret = aci_gatt_srv_add_char(&gap_chrs[3U], gap_srvc_handle);
        if (ret != BLE_STATUS_SUCCESS)
        {
            return ret;
        }
    }

    /**
     * Set default device name.
     */
    Gap_profile_set_dev_name(0U, sizeof(default_dev_name),
                             (uint8_t *)default_dev_name);

    return ret;
}

void Gap_profile_get_handles(uint16_t *srvc_h,
                             uint16_t *dev_name_h,
                             uint16_t *appearance_h)
{
    *srvc_h = aci_gatt_srv_get_service_handle(&gap_srvc);
    *dev_name_h = aci_gatt_srv_get_char_decl_handle(&gap_chrs[0U]);
    *appearance_h = aci_gatt_srv_get_char_decl_handle(&gap_chrs[1U]);
}

tBleStatus Gap_profile_set_dev_name(uint16_t offset,
                                    uint16_t length,
                                    uint8_t *dev_name_p)
{
    uint16_t handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[0U]) + 1U;

    return Gap_profile_set_char_value(handle, offset, length, dev_name_p);
}

tBleStatus Gap_profile_set_appearance(uint16_t offset,
                                      uint16_t length,
                                      uint8_t *appearance_p)
{
    uint16_t handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[1U]) + 1U;

    return Gap_profile_set_char_value(handle, offset, length, appearance_p);
}

tBleStatus Gap_profile_set_pref_conn_par(uint16_t offset,
                                         uint16_t length,
                                         uint8_t *pref_conn_param_p)
{
    uint16_t handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[2U]) + 1U;

    return Gap_profile_set_char_value(handle, offset, length, pref_conn_param_p);
}

tBleStatus Gap_profile_set_char_value(uint16_t attr_h,
                                      uint16_t val_offset,
                                      uint16_t val_length,
                                      uint8_t *val_p)
{
    uint8_t i;
    uint16_t handle;

    /**
     * Search for GAP characteristic.
     */
    for (i = 0U; i < (sizeof(gap_chrs) / sizeof(gap_chrs[0U])); i++)
    {
        handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[i]);
        if ((handle != BLE_ATT_INVALID_ATTR_HANDLE) &&
            ((handle + 1U) == attr_h))
        {
            break;
        }
    }

    if (i == (sizeof(gap_chrs) / sizeof(gap_chrs[0U])))
    {
        /**
         * The given attribute handle is not registered for GAP service.
         */
        return BLE_STATUS_INVALID_PARAMS;
    }

    if ((val_offset + val_length) > gap_chrs[i].val_buffer_p->buffer_len)
    {
        /**
         * Invalid value length.
         */
        return BLE_STATUS_INVALID_PARAMS;
    }

    /**
     * Write characteristic value.
     */
    memcpy(&gap_chrs[i].val_buffer_p->buffer_p[val_offset], val_p, val_length);
    if ((gap_chrs[i].val_buffer_p->op_flags & BLE_GATT_SRV_OP_VALUE_VAR_LENGTH_FLAG) != 0U)
    {
        gap_chrs[i].val_buffer_p->val_len = val_length;
    }

    return BLE_STATUS_SUCCESS;
}

tBleStatus Gap_profile_set_access_permission(uint16_t attr_h, uint8_t perm)
{
    uint16_t handle;

    perm &= BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK;

    /**
     * Check if it is the device name char;
     */
    handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[0U]);
    if ((handle != BLE_ATT_INVALID_ATTR_HANDLE) && ((handle + 1U) == attr_h))
    {
        gap_chrs[0U].properties &= ~BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK;
        gap_chrs[0U].properties |= perm;

        return BLE_STATUS_SUCCESS;
    }

    /**
     * Check if it is the appearance char;
     */
    handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[1U]);
    if ((handle != BLE_ATT_INVALID_ATTR_HANDLE) && ((handle + 1U) == attr_h))
    {
        gap_chrs[1U].properties &= ~BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK;
        gap_chrs[1U].properties |= perm;

        return BLE_STATUS_SUCCESS;
    }

    return BLE_STATUS_FAILED;
}

tBleStatus Gap_profile_set_security_permission(uint16_t attr_h, uint8_t perm)
{
    uint16_t handle;

    /**
     * Check if it is the device name char;
     */
    handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[0U]);
    if ((handle != BLE_ATT_INVALID_ATTR_HANDLE) && ((handle + 1U) == attr_h))
    {
        if ((perm & (BLE_GATT_SRV_PERM_ENCRY_READ |
                     BLE_GATT_SRV_PERM_AUTHEN_READ)) != 0U)
        {
            /**
             * <<Readable without authentication or authorization when
             *   discoverable.>>
             *
             * Table 12.3: Device Name characteristic
             * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part C page 1395
             */
            return BLE_STATUS_NOT_ALLOWED;
        }
        gap_chrs[0U].permissions = perm;

        return BLE_STATUS_SUCCESS;
    }

    /**
     * Check if it is the appearance char;
     */
    handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[1U]);
    if ((handle != BLE_ATT_INVALID_ATTR_HANDLE) && ((handle + 1U) == attr_h))
    {
        if ((perm & (BLE_GATT_SRV_PERM_ENCRY_READ |
                     BLE_GATT_SRV_PERM_AUTHEN_READ)) != 0U)
        {
            /**
             * <<Readable without authentication or authorization.>>
             *
             * Table 12.4: Appearance characteristic
             * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part C page 1395
             */
            return BLE_STATUS_NOT_ALLOWED;
        }
        gap_chrs[1U].permissions = perm;

        return BLE_STATUS_SUCCESS;
    }

    /**
     * Check if it is the Peripheral Preferred Connection Parameters characteristic
     */
    handle = aci_gatt_srv_get_char_decl_handle(&gap_chrs[2U]);
    if ((handle != BLE_ATT_INVALID_ATTR_HANDLE) && ((handle + 1U) == attr_h))
    {
        if ((perm & (BLE_GATT_SRV_PERM_AUTHEN_WRITE |
                     BLE_GATT_SRV_PERM_ENCRY_WRITE)) != 0U)
        {
            /**
             * <<Not writable.>>
             *
             * Table 12.5: Peripheral Preferred Connection Parameters characteristic
             * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part C page 1396
             */
            return BLE_STATUS_NOT_ALLOWED;
        }
        gap_chrs[2U].permissions = perm;

        return BLE_STATUS_SUCCESS;
    }

    return BLE_STATUS_FAILED;
}

uint16_t Gap_profile_get_service_handle(void)
{
    return aci_gatt_srv_get_service_handle((ble_gatt_srv_def_t *)&gap_srvc);
}

ble_gatt_srv_def_t *Gap_profile_get_service_definition_p(void)
{
    return (ble_gatt_srv_def_t *)&gap_srvc;
}

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
