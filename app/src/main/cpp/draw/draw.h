#pragma once
#include "imgui.h"
#include "definition.h" //定义
#include "内存操作.h"
#include <jni.h>
#include <string>
#include <sstream>
#include <stdio.h>

void 功能实现();
ImVec4 ImColorFromHex(const std::string& hexColor);

// 将时间戳（毫秒）转换为北京时间字符串
std::string convertTimestampToBeijingTime(long long timestamp_ms) {
    // 将毫秒转换为秒
    time_t timestamp_s = timestamp_ms / 1000;
    // 转换为UTC时间
    std::tm* utc_time = std::gmtime(&timestamp_s);
    // 转换为北京时间（UTC+8）
    std::tm beijing_time = *utc_time;
    beijing_time.tm_hour += 8; // 加上8小时
    // 调整时间结构，确保日期正确
    mktime(&beijing_time);
    // 格式化输出
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &beijing_time);
    return std::string(buffer);
}
void DrawGradientText(const char* text, ImVec4 startColor, ImVec4 endColor) {
    const char* p = text;
    const char* p_end = p + strlen(p);

    ImVec4 colorStep = ImVec4(
        (endColor.x - startColor.x) / (p_end - p),
        (endColor.y - startColor.y) / (p_end - p),
        (endColor.z - startColor.z) / (p_end - p),
        (endColor.w - startColor.w) / (p_end - p)
    );

    ImVec4 currentColor = startColor;

    for (; p < p_end; p++) {
        ImGui::TextColored(currentColor, "%c", *p);
        currentColor.x += colorStep.x;
        currentColor.y += colorStep.y;
        currentColor.z += colorStep.z;
        currentColor.w += colorStep.w;
        ImGui::SameLine(0, 0);
    }
}

// 定义语言选项
const char* Language[] = { "English", "中文" };
static int current_language = 1; 




bool draw_imgui()
{
    ImGui::Begin(window_title.c_str());
    if (ImGui::BeginTabBar("TabBar"))
    {
        if (ImGui::BeginTabItem(languages[current_language].home_main))
        {
            if (ImGui::CollapsingHeader(languages[current_language].esp_header))
            {
                ImGui::Checkbox(languages[current_language].esp_box, &Esp.Box);
                ImGui::SameLine(0, 0);
                ImGui::Checkbox(languages[current_language].esp_name, &Esp.Name);
                ImGui::SameLine();
                ImGui::Checkbox(languages[current_language].esp_line, &Esp.Line);
                ImGui::Checkbox(languages[current_language].esp_health, &Esp.Health);
                ImGui::SameLine();
                ImGui::Checkbox(languages[current_language].esp_distance, &Esp.Distance);
                ImGui::SameLine();
                ImGui::Checkbox(languages[current_language].esp_teamid, &Esp.TeamID);
            }
            ImGui::Separator();
            if (ImGui::CollapsingHeader(languages[current_language].feature_header))
            {
				

            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(languages[current_language].settings_header))
        {
            const char* themes[] = { "Dark", "Light", "Classic" };
            static int current_theme = 0; // 当前选择的主题

            // 创建下拉选择框
            if (ImGui::Combo(languages[current_language].theme_combo, &current_theme, themes, IM_ARRAYSIZE(themes)))
            {
                // 根据选择的主题切换ImGui样式
                switch (current_theme)
                {
                    case 0: ImGui::StyleColorsDark(); break;       // 暗色主题
                    case 1: ImGui::StyleColorsLight(); break;      // 亮色主题
                    case 2: ImGui::StyleColorsClassic(); break;    // 经典主题
                }
            }
            
            ImGui::Separator();

            // 创建下拉选择框
            if (ImGui::Combo(languages[current_language].language_combo, &current_language, Language, IM_ARRAYSIZE(Language)))
            {
                // 动态更新语言文本
            }
            ImGui::Separator();
            if (ImGui::Button(languages[current_language].exit, ImVec2(200, 100)))
            {
                return true;
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(languages[current_language].user_header))
        {
			static ImVec4 color = ImColor(60, 170, 222, 255);  // RGBA颜色
			ImGui::ColorEdit3("Color", (float*)&color);
            ImGui::Text("%s:", languages[current_language].kali_daoqi);
            ImGui::SameLine(0, 0);
            ImGui::TextColored(color, "2099-12-31"/*, convertTimestampToBeijingTime(1736507345000).c_str()*/);         
            ImGui::Text("%s:", languages[current_language].announcement);
            ImGui::SameLine(0, 0);
            ImGui::TextColored(color, "Null");
            ImGui::Separator();
            ImGui::Text("%s:", languages[current_language].versions);
            ImGui::SameLine(0, 0);
            ImGui::TextColored(color, "%s",new_versions);
            ImGui::Separator();
            ImGui::Text("%s:", languages[current_language].latest_versions);
            ImGui::SameLine(0, 0);
            ImGui::TextColored(color , "%s",new_versions);
            ImGui::Separator();
            ImGui::Text("%s: ", languages[current_language].status);
            ImGui::SameLine(0, 0);
            ImGui::TextColored(color, "Normal");
            ImGui::Separator();
			ImGui::Text("%s: ", languages[current_language].getmypid);
            ImGui::SameLine(0, 0);
            ImGui::TextColored(color , "%d",get_my_pid());
            ImGui::Separator();
            DrawGradientText(window_title.c_str(), ImColor(89, 222, 60), ImColor(222, 112, 60));
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar(); // 结束标签栏
    }

    ImGui::End();

    return false;
}




void 功能实现() {
	
}


ImVec4 ImColorFromHex(const std::string& hexColor) {
    std::string color = hexColor;
    if (color.size() > 0 && (color[0] == '#' || (color[0] == '0' && color[1] == 'x'))) {
        color = color.substr(1);
    }
    if (color.size() != 6 && color.size() != 8) {
        return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    unsigned int r, g, b, a = 255;
    std::istringstream(color.substr(0, 2)) >> std::hex >> r;
    std::istringstream(color.substr(2, 2)) >> std::hex >> g;
    std::istringstream(color.substr(4, 2)) >> std::hex >> b;
    if (color.size() == 8) {
        std::istringstream(color.substr(6, 2)) >> std::hex >> a;
    }
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
