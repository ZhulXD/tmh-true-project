#pragma once
#include <ctime>
#include <string>
#include "curl/curl.h"
#include "Tools.h"
#include "json.hpp"
#include "Includes/Logger.h"

using json = nlohmann::ordered_json;

#ifndef MOCK_AUTH_BYPASS
#define MOCK_AUTH_BYPASS 1
#endif

std::string title, version;
std::string UUID;

static std::string slotZ = "BYPASS_SLOT_01";
static std::string inVip = "100";
static std::string autoskillsZ = "true";
static std::string expired = "9999-12-31 23:59:59";
static std::string EXP = "PERMANENT ACCESS";
static std::string name = "DevUser";
static std::string device = "Android Device";
static std::string status = "Active";
static std::string floating = "true";
static std::string battleData = "true";
static std::string clientManager = "DEV_BYPASS_MODE";

std::string g_Token = "MOCK_VALID_TOKEN_12345", g_Auth = "MOCK_VALID_TOKEN_12345";
bool bValid = true;
bool bInitDone = true;

namespace SignIN
{
    static bool user = true;
}

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;
    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

std::string Login(JavaVM *jvm, const char *user_key, bool *success) {
    std::string safeKey = (user_key != nullptr) ? user_key : "";
    std::string devUUID = "MOCK_DEVICE_UUID_0000";

    if (jvm != nullptr) {
        JNIEnv *env = nullptr;
        if (jvm->AttachCurrentThread(&env, 0) == JNI_OK && env != nullptr) {
            auto looperClass = env->FindClass("android/os/Looper");
            if (looperClass) {
                auto prepareMethod = env->GetStaticMethodID(looperClass, "prepare", "()V");
                if (prepareMethod) {
                    env->CallStaticVoidMethod(looperClass, prepareMethod);
                }
                if (env->ExceptionCheck()) env->ExceptionClear();
            }

            jclass activityThreadClass = env->FindClass("android/app/ActivityThread");
            if (activityThreadClass) {
                jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, "sCurrentActivityThread", "Landroid/app/ActivityThread;");
                if (sCurrentActivityThreadField) {
                    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
                    if (sCurrentActivityThread) {
                        jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, "mInitialApplication", "Landroid/app/Application;");
                        if (mInitialApplicationField) {
                            jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
                            if (mInitialApplication) {
                                std::string hwid = safeKey;
                                hwid += GetAndroidID(env, mInitialApplication);
                                hwid += GetDeviceModel(env);
                                hwid += GetDeviceBrand(env);
                                hwid += GetDeviceManufacturer(env);
                                hwid += GetDeviceSerial(env);
                                hwid += GetDeviceFingerPrint(env);
                                hwid += GetSDKVersion(env);
                                hwid += GetDeviceID(env);
                                devUUID = GetDeviceUniqueIdentifier(env, hwid.c_str());
                            }
                        }
                    }
                }
            }
            if (env->ExceptionCheck()) env->ExceptionClear();
            jvm->DetachCurrentThread();
        }
    }

#if MOCK_AUTH_BYPASS
    time_t now = time(nullptr);
    std::string mockSeed = "MLBB-TOKEN-" + safeKey + "-" + devUUID + "-" + std::to_string(now);
    std::string tokenHash = Tools::CalcMD5(mockSeed);

    g_Token = tokenHash;
    g_Auth  = tokenHash;
    bValid  = true;
    SignIN::user = true;

    slotZ         = "BYPASS_DEV_SLOT";
    inVip         = "100";
    autoskillsZ   = "true";
    expired       = "9999-12-31 23:59:59";
    EXP           = "PERMANENT DEV ACCESS";
    name          = "DevUser";
    device        = "Android Dev Device";
    status        = "Active (Bypass)";
    floating      = "true";
    battleData    = "true";
    clientManager = "DEV_BYPASS_MODE";

    if (success != nullptr) {
        *success = true;
    }

    LOGI("[AUTH_BYPASS_AUDIT] Login bypass triggered | Key: '%s' | UUID: '%s' | Token: '%s'",
         safeKey.c_str(), devUUID.c_str(), tokenHash.c_str());

    return "Login Successful (Bypass Active)";
#else
    std::string UUID = devUUID;
    std::string errMsg;
    
    if (success != nullptr) {
        *success = false;
    }
    
    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;
    
    CURL *curl = curl_easy_init();
    CURLcode res;
    
    if (curl) {
        std::string bangrendi = "https://t0pgamemurah.xyz/freeKey/freeKey.php";
        curl_easy_setopt(curl, CURLOPT_URL, bangrendi.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(headers, "Charset: UTF-8");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Mobile Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        std::string data = "game=MLBB";
        data += "&user_key=" + safeKey;
        data += "&serial=" + UUID;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
        
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            
            if (http_code != 200) {
                errMsg = "Server Error (HTTP " + std::to_string(http_code) + "): Invalid Key or Server Down.";
                LOGI("[AUTH_AUDIT] Remote auth returned HTTP %ld for key '%s'", http_code, safeKey.c_str());
            } else if (chunk.size == 0 || chunk.memory == nullptr) {
                errMsg = "Invalid Key: Empty server response.";
                LOGI("[AUTH_AUDIT] Remote auth returned empty body for key '%s'", safeKey.c_str());
            } else {
                std::string body(chunk.memory, chunk.size);
                size_t firstNonWs = body.find_first_not_of(" \t\n\r");
                if (firstNonWs == std::string::npos || (body[firstNonWs] != '{' && body[firstNonWs] != '[')) {
                    errMsg = "Invalid License Key.";
                    LOGI("[AUTH_AUDIT] Non-JSON payload received for key '%s'", safeKey.c_str());
                } else {
                    try {
                        json result = json::parse(body);
                        if (result.contains("status") && result["status"] == true) {
                            std::string token = result["data"]["token"].get<std::string>();
                            time_t rng = result["data"]["rng"].get<time_t>();
                            
                            slotZ         = result["data"].value("device", "");
                            expired       = result["data"].value("EXP_MOD", "");
                            inVip         = result["data"].value("iniVip", "");
                            autoskillsZ   = result["data"].value("AutoSkills", "");
                            clientManager = result["data"].value("client", "");
                            
                            battleData = "true";
                            if (rng + 30 > time(0)) {
                                std::string auth = "MLBB-" + safeKey + "-" + UUID + "-Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E";
                                std::string outputAuth = Tools::CalcMD5(auth);
                                g_Token = token;
                                g_Auth = outputAuth;
                                
                                if (g_Token == g_Auth) {
                                    if (success != nullptr) {
                                        *success = true;
                                    }
                                    errMsg = "Login Success";
                                } else {
                                    errMsg = "Invalid Key: Token mismatch.";
                                }
                            } else {
                                errMsg = "Invalid Key: Request timestamp expired.";
                            }
                        } else {
                            if (result.contains("reason") && result["reason"].is_string()) {
                                errMsg = result["reason"].get<std::string>();
                            } else {
                                errMsg = "Invalid License Key.";
                            }
                            LOGI("[AUTH_AUDIT] License validation rejected key '%s': %s", safeKey.c_str(), errMsg.c_str());
                        }
                    } catch (const json::exception &e) {
                        errMsg = "Invalid License Key.";
                        LOGI("[AUTH_AUDIT] JSON parsing exception caught for key '%s': %s", safeKey.c_str(), e.what());
                    }
                }
            }
        } else {
            errMsg = "Connection failed: " + std::string(curl_easy_strerror(res));
            LOGI("[AUTH_AUDIT] CURL perform failed: %s", errMsg.c_str());
        }
        curl_easy_cleanup(curl);
    } else {
        errMsg = "Failed to initialize network client.";
    }
    
    if (chunk.memory != nullptr) {
        free(chunk.memory);
    }
    
    return errMsg;
#endif
}

static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

bool download_file(std::string url, std::string path){
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if (curl) {   
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        
        FILE *file = fopen(path.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        CURLcode result = curl_easy_perform(curl);
        
        fclose(file);
        curl_easy_cleanup(curl);

        if (result == CURLE_OK) {
            return true;
        } else {
            return false;
        }
    }
    curl_global_cleanup();
    return false;
}
