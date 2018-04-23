// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ========================================================================
//
// Tests the constants that vary depending on the customization of Omaha.
// The test checks for the Google Update variations, but can be modified for
// your purposes.

#include <tchar.h>
#include "omaha/base/const_addresses.h"
#include "omaha/base/const_code_signing.h"
#include "omaha/base/const_config.h"
#include "omaha/base/const_debug.h"
#include "omaha/base/const_object_names.h"
#include "omaha/base/constants.h"
#include "omaha/base/logging.h"
#include "omaha/base/process.h"
#include "omaha/base/utils.h"
#include "omaha/common/config_manager.h"
#include "omaha/common/const_goopdate.h"
#include "omaha/common/const_group_policy.h"
#include "omaha/common/omaha_customization_proxy_clsid.h"
#include "omaha/testing/omaha_customization_test.h"

// TODO(omaha): Make use of EXPECT_STREQ, etc.

namespace omaha {

TEST(OmahaCustomizationTest, Constants_BuildFiles) {
  // Primary main.scons values.

  // TODO(omaha): Most of these tests are of extremely questionable
  // value, as they're just checking that certain #defines exist and
  // haven't changed.  But, unanticipated changes to most of these
  // would cause build breaks anyways!  Consider deleting them.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ("Brave Inc.", FULL_COMPANY_NAME_ANSI);
  EXPECT_STREQ("Brave", SHORT_COMPANY_NAME_ANSI);
  EXPECT_STREQ("Update", PRODUCT_NAME_ANSI);

  EXPECT_STREQ("brave", COMPANY_DOMAIN_BASE_ANSI);
  EXPECT_STREQ("brave.com", COMPANY_DOMAIN_ANSI);

  EXPECT_STREQ("Brave Update", OMAHA_APP_NAME_ANSI);
#endif  // GOOGLE_UPDATE_BUILD

  EXPECT_STREQ("brapdate", MAIN_DLL_BASE_NAME_ANSI);

  const GUID kActualProxyClsidIsMachineGuid = PROXY_CLSID_IS_MACHINE;
  EXPECT_TRUE(::IsEqualGUID(kProxyClsidIsMachineGuid,
                            kActualProxyClsidIsMachineGuid));

  const GUID kActualProxyClsidIsUserGuid = PROXY_CLSID_IS_USER;
  EXPECT_TRUE(::IsEqualGUID(kProxyClsidIsUserGuid,
                            kActualProxyClsidIsUserGuid));

  // VERSION file values. Only the relatively stable ones are tested.
  // The versions may or may not match in non-Google Update builds.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ("9", ONECLICK_PLUGIN_VERSION_ANSI);
  // TODO(omaha): Change the name to ANSI.
  EXPECT_STREQ("3", UPDATE_PLUGIN_VERSION_ANSI);
#else
  std::wcout << _T("Did not test version values.") << std::endl;
#endif

  // Primary omaha_version_utils values.
  EXPECT_STREQ(_T("npBraveOneClick"), ONECLICK_PLUGIN_NAME);
  EXPECT_STREQ(_T("npBraveUpdate"), UPDATE_PLUGIN_NAME);
  EXPECT_STREQ(_T("BrapdateBho"), BHO_NAME);

  // Filenames from omaha_version_utils.
  EXPECT_STREQ(
      _T("npBraveOneClick") _T(ONECLICK_PLUGIN_VERSION_ANSI) _T(".dll"),
      ONECLICK_PLUGIN_FILENAME);
  EXPECT_STREQ(_T("npBraveUpdate") _T(UPDATE_PLUGIN_VERSION_ANSI) _T(".dll"),
               UPDATE_PLUGIN_FILENAME);
  EXPECT_STREQ(_T("BrapdateBho.dll"), BHO_FILENAME);
}

TEST(OmahaCustomizationTest, Constants_Names) {
  // Company and product names.

  // TODO(omaha): Most of these tests are of extremely questionable
  // value, as they're just checking that certain #defines exist and
  // haven't changed.  But, unanticipated changes to most of these
  // would cause build breaks anyways!  Consider deleting them.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ(_T("Brave Inc."), kFullCompanyName);
  EXPECT_STREQ(_T("Brave"), SHORT_COMPANY_NAME);
  EXPECT_STREQ(_T("Brave"), kShortCompanyName);
  EXPECT_STREQ(_T("Update"), PRODUCT_NAME);

  EXPECT_STREQ(_T("brave.com"), COMPANY_DOMAIN);

  // Full app name.
  EXPECT_STREQ(_T("Brave Update"), kAppName);

  // Identifiers.
  EXPECT_STREQ(_T("Brave"), COMPANY_NAME_IDENTIFIER);
  EXPECT_STREQ(_T("Update"), PRODUCT_NAME_IDENTIFIER);
  EXPECT_STREQ(_T("BraveUpdate"), APP_NAME_IDENTIFIER);

  // Other values based on the app name.
  EXPECT_STREQ(_T("_Brave_Update_"), kLockPrefix);
#endif  // GOOGLE_UPDATE_BUILD

  // Filename bases
  EXPECT_STREQ(_T("BraveUpdate"), MAIN_EXE_BASE_NAME);
  EXPECT_STREQ(_T("goopdate"), MAIN_DLL_BASE_NAME);
}

TEST(OmahaCustomizationTest, Constants_Filenames) {
  EXPECT_STREQ(_T("BraveUpdate.exe"), kOmahaShellFileName);
  EXPECT_STREQ(_T("BraveCrashHandler.exe"), kCrashHandlerFileName);
  EXPECT_STREQ(_T("BraveCrashHandler64.exe"), kCrashHandler64FileName);
  EXPECT_STREQ(_T("goopdate.dll"), kOmahaDllName);
  EXPECT_STREQ(_T("goopdateres_%s.dll"), kOmahaResourceDllNameFormat);
  EXPECT_STREQ(_T("BraveUpdateBroker.exe"), kOmahaBrokerFileName);
  EXPECT_STREQ(_T("BraveUpdateCore.exe"), kOmahaCoreFileName);
  EXPECT_STREQ(_T("BraveUpdateOnDemand.exe"), kOmahaOnDemandFileName);
  EXPECT_STREQ(_T("BraveUpdateWebPlugin.exe"), kOmahaWebPluginFileName);
  EXPECT_STREQ(_T("BraveUpdateSetup.exe"), kOmahaMetainstallerFileName);
  EXPECT_STREQ(_T("BraveUpdateComRegisterShell64.exe"),
               kOmahaCOMRegisterShell64);
  EXPECT_STREQ(_T("psmachine.dll"), kPSFileNameMachine);
  EXPECT_STREQ(_T("psmachine_64.dll"), kPSFileNameMachine64);
  EXPECT_STREQ(_T("psuser.dll"), kPSFileNameUser);
  EXPECT_STREQ(_T("psuser_64.dll"), kPSFileNameUser64);
}

TEST(OmahaCustomizationTest, Constants_Certificate) {
  EXPECT_STREQ(_T("Brave Inc"), kCertificateSubjectName);
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_String) {
  EXPECT_STREQ(_T("{B131C935-9BE6-41DA-9599-1F776BEB8019}"), GOOPDATE_APP_ID);
  EXPECT_STREQ(_T("{B131C935-9BE6-41DA-9599-1F776BEB8019}"),
               kBraveUpdateAppId);
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_GUID) {
  const GUID kExpectedBraveUpdateGuid =
      {0x430FD4D0, 0xB729, 0x4F61,
       {0xAA, 0x34, 0x91, 0x52, 0x64, 0x81, 0x79, 0x9D}};
  EXPECT_TRUE(::IsEqualGUID(kExpectedBraveUpdateGuid, kGoopdateGuid));
  EXPECT_STREQ(_T("{B131C935-9BE6-41DA-9599-1F776BEB8019}"),
               GuidToString(kGoopdateGuid));
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_GUIDAndStringMatch) {
  EXPECT_STREQ(kBraveUpdateAppId, GuidToString(kGoopdateGuid));
}

TEST(OmahaCustomizationTest, Constants_Directories) {
  EXPECT_STREQ(_T("Offline"), OFFLINE_DIR_NAME);
  EXPECT_STREQ(_T("Brave"), OMAHA_REL_COMPANY_DIR);
  EXPECT_STREQ(_T("Brave\\CrashReports"), OMAHA_REL_CRASH_DIR);
  EXPECT_STREQ(_T("Brave\\Update"), OMAHA_REL_GOOPDATE_INSTALL_DIR);
  EXPECT_STREQ(_T("Brave\\Update\\Log"), OMAHA_REL_LOG_DIR);
  EXPECT_STREQ(_T("Brave\\Update\\Offline"),
                  OMAHA_REL_OFFLINE_STORAGE_DIR);
  EXPECT_STREQ(_T("Brave\\Update\\Download"),
                  OMAHA_REL_DOWNLOAD_STORAGE_DIR);
  EXPECT_STREQ(_T("Brave\\Update\\Install"),
                  OMAHA_REL_INSTALL_WORKING_DIR);
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys_NotCustomized) {
  EXPECT_STREQ(_T("HKLM"), MACHINE_KEY_NAME);
  EXPECT_STREQ(_T("HKLM\\"), MACHINE_KEY);
  EXPECT_STREQ(_T("HKCU"), USER_KEY_NAME);
  EXPECT_STREQ(_T("HKCU\\"), USER_KEY);
  EXPECT_STREQ(_T("HKU\\"), USERS_KEY);
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys) {
  EXPECT_STREQ(_T("Software\\Brave\\"), COMPANY_MAIN_KEY);
  EXPECT_STREQ(_T("Software\\Brave\\Update\\"), GOOPDATE_MAIN_KEY);
  EXPECT_STREQ(_T("Software\\Brave\\Update\\Clients\\"), GOOPDATE_REG_RELATIVE_CLIENTS);  // NOLINT
  EXPECT_STREQ(_T("Software\\Brave\\Update\\ClientState\\"), GOOPDATE_REG_RELATIVE_CLIENT_STATE);  // NOLINT
  EXPECT_STREQ(_T("Software\\Brave\\Update\\ClientStateMedium\\"), GOOPDATE_REG_RELATIVE_CLIENT_STATE_MEDIUM);  // NOLINT
  EXPECT_STREQ(_T("Software\\Policies\\Brave\\"), COMPANY_POLICIES_MAIN_KEY);           // NOLINT
  EXPECT_STREQ(_T("Software\\Policies\\Brave\\Update\\"), GOOPDATE_POLICIES_RELATIVE);  // NOLINT

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\"), USER_REG_GOOGLE);
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\"), USER_REG_UPDATE);
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\Clients\\"), USER_REG_CLIENTS);  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\Clients\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), USER_REG_CLIENTS_GOOPDATE);  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\ClientState\\"), USER_REG_CLIENT_STATE);  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\ClientState\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), USER_REG_CLIENT_STATE_GOOPDATE);  // NOLINT

  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\"), MACHINE_REG_GOOGLE);
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\"), MACHINE_REG_UPDATE);
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\Clients\\"), MACHINE_REG_CLIENTS);  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\Clients\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), MACHINE_REG_CLIENTS_GOOPDATE);  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientState\\"), MACHINE_REG_CLIENT_STATE);  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientState\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), MACHINE_REG_CLIENT_STATE_GOOPDATE);  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientStateMedium\\"), MACHINE_REG_CLIENT_STATE_MEDIUM);  // NOLINT

  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\UpdateDev\\"), MACHINE_REG_UPDATE_DEV);  // NOLINT
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys_GroupPolicy) {
  EXPECT_STREQ(_T("Software\\Policies\\Brave\\Update\\"), GOOPDATE_POLICIES_RELATIVE);  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Policies\\Brave\\Update\\"), kRegKeyGoopdateGroupPolicy);  // NOLINT
}

TEST(OmahaCustomizationTest, Constants_RegistryValues) {
  EXPECT_STREQ(_T("Brave Update"), kRunValueName);
}

TEST(OmahaCustomizationTest, Constants_MsiMsp) {
  EXPECT_STREQ(_T("BraveUpdateHelper.msi"), kHelperInstallerName);
  EXPECT_STREQ(_T("{A92DAB39-4E2C-4304-9AB6-BC44E68B55E2}"),
               kHelperInstallerProductGuid);
  EXPECT_STREQ(_T("BraveUpdateHelperPatch.msp"), kHelperPatchName);
  EXPECT_STREQ(_T("{E0D0D2C9-5836-4023-AB1D-54EC3B90AD03}"), kHelperPatchGuid);
}

TEST(OmahaCustomizationTest, Constants_CompatibleMinimumOlderShellVersion) {
  EXPECT_EQ(0x00010003001A0001, kCompatibleMinimumOlderShellVersion);
}

TEST(OmahaCustomizationTest, Constants_BrandCode) {
  EXPECT_STREQ(_T("GGLS"), kDefaultBraveUpdateBrandCode);
}

TEST(OmahaCustomizationTest, Constants_Addresses) {
  EXPECT_STREQ(_T("www.brave.com"), kGoogleHttpServer);
  EXPECT_STREQ(_T("tools.brave.com"), kGoopdateServer);
  EXPECT_STREQ(_T("https://update.brave.com/service/update2"),
               kUrlUpdateCheck);
  EXPECT_STREQ(_T("https://update.brave.com/service/update2"), kUrlPing);
  EXPECT_STREQ(_T("https://clients2.brave.com/cr/report"), kUrlCrashReport);
  EXPECT_STREQ(_T("https://www.brave.com/support/installer/?"), kUrlMoreInfo);
  EXPECT_STREQ(_T("https://clients2.brave.com/service/check2"),
               kUrlCodeRedCheck);
  EXPECT_STREQ(_T("https://clients5.brave.com/tbproxy/usagestats"),
               kUrlUsageStatsReport);
}

TEST(OmahaCustomizationTest, Constants_Config) {
  EXPECT_STREQ(_T("Software\\BraveUpdate\\Shared"), kCiRegKeyShared);
}

TEST(OmahaCustomizationTest, Constants_Debug) {
  EXPECT_STREQ(_T("BraveUpdate-debug"), kCiDebugDirectory);
}

TEST(OmahaCustomizationTest, Constants_Logging) {
  EXPECT_STREQ(_T("BraveUpdate.ini"), kLogConfigFileName);
  EXPECT_STREQ(_T("BraveUpdate.log"), kDefaultLogFileName);
}

// These should not change during customization.
TEST(OmahaCustomizationTest, Constants_ObjectNames_Prefixes) {
  EXPECT_STREQ(_T("Global\\G"), kGlobalPrefix);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_Pipes) {
  EXPECT_STREQ(_T("\\\\.\\pipe\\BraveCrashServices"), kCrashPipeNamePrefix);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_MutexesAndEvents) {
  EXPECT_STREQ(_T("{A9A86B93-B54E-4570-BE89-42418507707B}"), kSetupMutex);
  EXPECT_STREQ(_T("{A0C1F415-D2CE-4ddc-9B48-14E56FD55162}"), kShutdownEvent);
  EXPECT_STREQ(_T("{B5665124-2B19-40e2-A7BC-B44321E72C4B}"),
               kCoreSingleInstance);
  EXPECT_STREQ(_T("{C4F406E5-F024-4e3f-89A7-D5AB7663C3CD}"),
               kCrashHandlerSingleInstance);
  EXPECT_STREQ(_T("{D0BB2EF1-C183-4cdb-B218-040922092869}"),
               kUpdateAppsSingleInstance);
  EXPECT_STREQ(_T("%s-{F707E94F-D66B-4525-AD84-B1DA87D6A971}"),
               kInstallAppSingleInstance);
  EXPECT_STREQ(_T("{0A175FBE-AEEC-4fea-855A-2AA549A88846}"),
               kInstallManagerSerializer);
  EXPECT_STREQ(_T("{C68009EA-1163-4498-8E93-D5C4E317D8CE}"),
               kMetricsSerializer);
  EXPECT_STREQ(_T("{66CC0160-ABB3-4066-AE47-1CA6AD5065C8}"),
               kRegistryAccessMutex);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_SharedMemory) {
  EXPECT_STREQ(_T("Global\\BraveUpdate3"),
                  kBraveUpdate3SharedMemoryName);
  EXPECT_STREQ(_T("Global\\BraveUpdateCore"),
                  kBraveUpdateCoreSharedMemoryName);
}

TEST(OmahaCustomizationTest, Constants_Services) {
  EXPECT_STREQ(_T("gupdate_service_name"), kRegValueServiceName);
  EXPECT_STREQ(_T("gupdatem_service_name"), kRegValueMediumServiceName);
  EXPECT_STREQ(_T("gupdate_task_name_c"), kRegValueTaskNameC);
  EXPECT_STREQ(_T("gupdate_task_name_ua"), kRegValueTaskNameUA);

  EXPECT_STREQ(_T("gupdate"), kServicePrefix);
  EXPECT_STREQ(_T("gupdatem"), kMediumServicePrefix);

  EXPECT_STREQ(_T("BraveUpdate.exe"), kServiceFileName);
}

TEST(OmahaCustomizationTest, Constants_ScheduledTasks) {
  EXPECT_STREQ(_T("BraveUpdateTaskUser"), kScheduledTaskNameUserPrefix);
  EXPECT_STREQ(_T("BraveUpdateTaskMachine"), kScheduledTaskNameMachinePrefix);    // NOLINT
}

TEST(OmahaCustomizationTest, Constants_Plugins) {
  EXPECT_STREQ(_T("Brave.OneClickCtrl.") _T(ONECLICK_PLUGIN_VERSION_ANSI),
                  kOneClickProgId);
  EXPECT_STREQ(
      "application/x-vnd.brave.oneclickctrl." ONECLICK_PLUGIN_VERSION_ANSI,
      kOneClickPluginMimeTypeAnsi);
}

TEST(OmahaCustomizationTest, Constants_HostCheck) {
  EXPECT_EQ(5, arraysize(kSiteLockPatternStrings));
  EXPECT_STREQ(_T("^(gears)|(mail)|(tools)|(www)|(desktop)|(pack)|(chrome)|(drive)\\.brave\\.com$"), kSiteLockPatternStrings[0]);  // NOLINT
  EXPECT_STREQ(_T("^www\\.brave\\.(ad)|(bg)|(ca)|(cn)|(cz)|(de)|(es)|(fi)|(fr)|(gr)|(hr)|(hu)|(it)|(ki)|(kr)|(lt)|(lv)|(nl)|(no)|(pl)|(pt)|(ro)|(ru)|(sk)|(sg)|(sl)|(sr)|(vn)$"), kSiteLockPatternStrings[1]);  // NOLINT
  EXPECT_STREQ(_T("^www\\.brave\\.co\\.(hu)|(id)|(il)|(it)|(jp)|(kr)|(th)|(uk)$"), kSiteLockPatternStrings[2]);  // NOLINT
  EXPECT_STREQ(_T("^www\\.brave\\.com\\.(ar)|(au)|(br)|(cn)|(et)|(gr)|(hr)|(ki)|(lv)|(om)|(pl)|(pt)|(ru)|(sg)|(sv)|(tr)|(vn)$"), kSiteLockPatternStrings[3]);  // NOLINT
}

//
// ConfigManager keys.
//

TEST(OmahaCustomizationTest, ConfigManager_RegistryKeys) {
  const ConfigManager& cm = *ConfigManager::Instance();

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\Clients\\"), cm.user_registry_clients());  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\Clients\\"), cm.machine_registry_clients());  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\Clients\\"), cm.registry_clients(false));  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\Clients\\"), cm.registry_clients(true));  // NOLINT

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\Clients\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.user_registry_clients_goopdate());  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\Clients\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.machine_registry_clients_goopdate());  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\Clients\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.registry_clients_goopdate(false));  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\Clients\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.registry_clients_goopdate(true));  // NOLINT

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\ClientState\\"), cm.user_registry_client_state());  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientState\\"), cm.machine_registry_client_state());  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\ClientState\\"), cm.registry_client_state(false));  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientState\\"), cm.registry_client_state(true));  // NOLINT

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\ClientState\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.user_registry_client_state_goopdate());  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientState\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.machine_registry_client_state_goopdate());  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\ClientState\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.registry_client_state_goopdate(false));  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientState\\{B131C935-9BE6-41DA-9599-1F776BEB8019}"), cm.registry_client_state_goopdate(true));  // NOLINT

  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\ClientStateMedium\\"), cm.machine_registry_client_state_medium());  // NOLINT

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\"), cm.user_registry_update());  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\"), cm.machine_registry_update());  // NOLINT
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\Update\\"), cm.registry_update(false));  // NOLINT
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\Update\\"), cm.registry_update(true));  // NOLINT

  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\"), cm.user_registry_brave());
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\"), cm.machine_registry_brave());
  EXPECT_STREQ(_T("HKCU\\Software\\Brave\\"), cm.registry_brave(false));
  EXPECT_STREQ(_T("HKLM\\Software\\Brave\\"), cm.registry_brave(true));
}

TEST(OmahaCustomizationTest, IsInternalUser) {
  if (IsBuildSystem()) {
  // The build system is not configured the same.
  // This may or may not be true in non-Google Update builds.
#ifdef GOOGLE_UPDATE_BUILD
    EXPECT_FALSE(ConfigManager::Instance()->IsInternalUser());
#else
  std::wcout << _T("Did not test IsInternalUser.") << std::endl;
#endif
  } else {
    EXPECT_TRUE(ConfigManager::Instance()->IsInternalUser());
  }
}

//
// Test helpers.
//

TEST(OmahaCustomizationTest, GetBraveUserPath) {
  EXPECT_STREQ(GetLocalAppDataPath() + SHORT_COMPANY_NAME + _T("\\"),
               GetBraveUserPath());
}

TEST(OmahaCustomizationTest, GetBraveUpdateUserPath) {
  EXPECT_STREQ(GetLocalAppDataPath() + SHORT_COMPANY_NAME + _T("\\")
                                     + PRODUCT_NAME + _T("\\"),
               GetBraveUpdateUserPath());
}

// Assumes Program Files is in the normal location.
TEST(OmahaCustomizationTest, GetBraveUpdateMachinePath) {
  CString expected_machine_path;
  EXPECT_SUCCEEDED(GetFolderPath(CSIDL_PROGRAM_FILES | CSIDL_FLAG_DONT_VERIFY,
                                 &expected_machine_path));
  expected_machine_path.Append(_T("\\") SHORT_COMPANY_NAME
                               _T("\\") PRODUCT_NAME);
  EXPECT_STREQ(expected_machine_path, GetBraveUpdateMachinePath());
}

}  // namespace omaha
