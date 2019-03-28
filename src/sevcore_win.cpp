/**************************************************************************
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************/

#ifdef _WIN32
#include "sevcore.h"
#include "utilities.h"
#include <openssl/hmac.h>
#include <sys/ioctl.h>      // for ioctl()
#include <sys/mman.h>       // for mmap() and friends
#include <errno.h>          // for errorno
#include <fcntl.h>          // for O_RDWR
#include <unistd.h>         // for close()
#include <stdexcept>        // for std::runtime_error()

SEVDevice::SEVDevice()
{
    mFd = open(DEFAULT_SEV_DEVICE, O_RDWR);
    if (mFd < 0) {
        throw std::runtime_error("Can't open " DEFAULT_SEV_DEVICE "!\n");
    }
}

SEVDevice::~SEVDevice()
{
    if (mFd >= 0) {
        close(mFd);
    }
    mFd = -1;
}

int SEVDevice::sev_ioctl(int cmd, void *data, int *cmd_ret)
{
    int ioctl_ret = -1;

    if(cmd == 0 || data || cmd_ret) {
    }

    return ioctl_ret;
}

int SEVDevice::factory_reset()
{
    int cmd_ret = -1;

    return cmd_ret;
}

static int get_platform_owner(void* data)
{
    return 0;
}

static int get_platform_es(void* data)
{
    return 0;
}

int SEVDevice::platform_status(uint8_t *data)
{
    int cmd_ret = -1;

    return cmd_ret;
}

int SEVDevice::pek_gen()
{
    int cmd_ret = -1;

    return cmd_ret;
}

bool SEVDevice::validate_pek_csr(SEV_CERT *pek_csr)
{
    if(pek_csr->Version     == 1                     &&
       pek_csr->PubkeyUsage == SEVUsagePEK           &&
       pek_csr->PubkeyAlgo  == SEVSigAlgoECDSASHA256 &&
       pek_csr->Sig1Usage   == SEVUsageInvalid       &&
       pek_csr->Sig1Algo    == SEVSigAlgoInvalid     &&
       pek_csr->Sig2Usage   == SEVUsageInvalid       &&
       pek_csr->Sig2Algo    == SEVSigAlgoInvalid) {
        return true;
    }
    else {
        return false;
    }
}

int SEVDevice::pek_csr(uint8_t *data, void *pek_mem, SEV_CERT *csr)
{
    int cmd_ret = -1;

    return cmd_ret;
}

int SEVDevice::pdh_gen()
{
    int cmd_ret = -1;

    return cmd_ret;
}

int SEVDevice::pdh_cert_export(uint8_t *data, void *pdh_cert_mem,
                               void *cert_chain_mem)
{
    int cmd_ret = -1;

    return cmd_ret;
}

// todo. dont want to be reading from a file. use openssl to generate
int SEVDevice::pek_cert_import(uint8_t *data,
                               SEV_CERT *pek_csr,
                               std::string& oca_priv_key_file,
                               std::string& oca_cert_file)
{
    int cmd_ret = -1;

    return cmd_ret;
}

// Must always pass in 128 bytes array, because of how linux /dev/sev ioctl works
int SEVDevice::get_id(void *data, void *id_mem, uint32_t id_length)
{
    int cmd_ret = -1;

    return cmd_ret;
}

static std::string display_build_info()
{
    SEVDevice sev_device;
    uint8_t status_data[sizeof(SEV_PLATFORM_STATUS_CMD_BUF)];
    SEV_PLATFORM_STATUS_CMD_BUF *status_data_buf = (SEV_PLATFORM_STATUS_CMD_BUF *)&status_data;
    int cmd_ret = -1;

    std::string api_major_ver = "API_Major: xxx";
    std::string api_minor_ver = "API_Minor: xxx";
    std::string build_id_ver  = "BuildID: xxx";

    cmd_ret = sev_device.platform_status(status_data);
    if (cmd_ret != 0)
        return "";

    char major_buf[4], minor_buf[4], build_id_buf[4];       // +1 for Null char
    sprintf(major_buf, "%d", status_data_buf->ApiMajor);
    sprintf(minor_buf, "%d", status_data_buf->ApiMinor);
    sprintf(build_id_buf, "%d", status_data_buf->BuildID);
    api_major_ver.replace(11, 3, major_buf);
    api_minor_ver.replace(11, 3, minor_buf);
    build_id_ver.replace(9, 3, build_id_buf);

    return api_major_ver + ", " + api_minor_ver + ", " + build_id_ver;
}

int SEVDevice::sys_info()
{
    int cmd_ret = 0;
    std::string cmd = "";
    std::string output = "";

    printf("-------------------------System Info-------------------------");
    printf("Coming soon...\n");

    // Print results of all execute_system_command calls
    printf("\n%s", output.c_str());

    std::string build_info = display_build_info();
    printf("Firmware Version: %s\n", build_info.c_str());

    printf("-------------------------------------------------------------\n\n");

    return cmd_ret;
}

/*
 * Note: You can not change the Platform Owner if Guests are running. That means
 *       the Platform cannot be in the WORKING state here. The ccp Kernel Driver
 *       will do its best to set the Platform state to whatever is required to
 *       run each command, but that does not include shutting down Guests to do so.
 */
int SEVDevice::set_self_owned()
{
    int cmd_ret = -1;

    return cmd_ret;
}

int SEVDevice::set_externally_owned(std::string& oca_priv_key_file,
                                    std::string& oca_cert_file)
{
    int cmd_ret = -1;

    return cmd_ret;
}


#endif
