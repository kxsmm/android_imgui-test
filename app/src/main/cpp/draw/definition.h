#pragma once
#include <iostream>
#include "imgui.h"
#include "内存操作.h"
const char* new_versions = "V1.0[beta]";
std::string window_title = "Moon " + std::string(new_versions);
struct sESPMenu {
    bool Bones;       // 骨骼
    bool Line;        // 线条
    bool Box;         // 边界框
    bool Health;      // 生命值
    bool Name;        // 名称
    bool Distance;    // 距离
    bool TeamID;      // 队伍ID
    bool Vehicle;     // 载具
    bool Radar;       // 雷达
} Esp{0};




struct sFeatureMenu {
    bool MoveSpeed; //移速
} Feature{0};


// 定义语言文本结构
typedef struct {
    const char* home_main;
    const char* esp_header;
    const char* esp_box;
    const char* esp_name;
    const char* esp_line;
    const char* esp_health;
    const char* esp_distance;
    const char* esp_teamid;
    const char* feature_header;
    const char* settings_header;
    const char* theme_combo;
    const char* language_combo;
    const char* exit;
    const char* user_header;
    const char* kali_daoqi;
    const char* announcement;
    const char* versions;
    const char* latest_versions;
    const char* status;
    const char* getmypid;
} LanguageText;

// 定义语言的文本
const LanguageText languages[] = {
    {
        "Main",
        "ESP", "Box", "Name", "Line", "Health", "Distance", "TeamID",
        "Feature",
        "Settings", "Theme", "Language", "Exit",
        "User", "Expiry time of Karmi", "Announcement", "Versions", "Latest_Versions", "Status", "Current Process PID",
    },
    {
        "主页",
        "绘制", "盒子", "名字", "线条", "血量", "距离", "队伍ID",
        "功能",
        "设置", "主题", "语言", "退出",
        "用户", "卡密到期时间", "公告", "版本", "最新版本", "状态", "当前进程PID",
    }
};



