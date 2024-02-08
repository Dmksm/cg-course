#pragma once
#include "stdafx.h"

class House 
{
public:
    House(wxPoint point, int width, int height)
        : m_leftTop(point)
        , m_height(height)
        , m_width(width)
    {}

    void Change(wxPoint point, int width, int height)
    {
        m_leftTop = point;
        m_height = height;
        m_width = width;
    }

    wxPoint GetLeftTopPoint()
    {
        return m_leftTop;
    }

    int GetWidth()
    {
        return m_width;
    }

    int GetHeight()
    {
        return m_height;
    }

    bool IsInsideHouse(wxPoint pos)
    {
        wxRect rect(m_leftTop.x, m_leftTop.y, m_width, m_height);
        return rect.Contains(pos);
    }

    void Render(wxDC& dc)
    {
        dc.SetBrush(*wxBLUE_BRUSH);
        DrawSky(dc);

        dc.SetBrush(*wxBLACK_BRUSH);
        DrawFlue(dc);

        dc.SetBrush(*wxCYAN_BRUSH);
        DrawRoof(dc);

        dc.SetBrush(*wxGREEN_BRUSH);
        DrawHouse(dc);

        dc.SetBrush(*wxYELLOW_BRUSH);
        DrawWindow(dc);

        dc.SetBrush(*wxYELLOW_BRUSH);
        DrawDoor(dc);

        dc.SetBrush(*wxYELLOW_BRUSH);
        DrawSun(dc);

        dc.SetBrush(*wxRED_BRUSH);
        DrawFence(dc);
    }
private:
    void DrawRoof(wxDC& dc)
    {
        std::vector<wxPoint> roof;
        roof.push_back({ int(m_leftTop.x + m_width * 0.25), m_leftTop.y });
        roof.push_back({ int(m_leftTop.x + m_width * 0.5), int(m_leftTop.y + m_height * 0.5) });
        roof.push_back({ m_leftTop.x, int(m_leftTop.y + m_height * 0.5) });
        dc.DrawPolygon(roof.size(), roof.data());
    }

    void DrawSky(wxDC& dc)
    {
        wxRect rect(m_leftTop.x, m_leftTop.y, m_width, m_height);
        dc.DrawRectangle(rect);
    }

    void DrawSun(wxDC& dc)
    {
        dc.DrawCircle(int(m_leftTop.x + m_width * 0.8), int(m_leftTop.y + m_height * 0.2), std::min(m_width * 0.05, m_height * 0.05));
    }

    void DrawWindow(wxDC& dc)
    {
        std::vector<wxPoint> window;
        window.push_back({ int(m_leftTop.x + m_width * 0.1), int(m_leftTop.y + m_height * 0.6) });
        window.push_back({ int(m_leftTop.x + m_width * 0.2), int(m_leftTop.y + m_height * 0.6) });
        window.push_back({ int(m_leftTop.x + m_width * 0.2), int(m_leftTop.y + m_height * 0.7) });
        window.push_back({ int(m_leftTop.x + m_width * 0.1), int(m_leftTop.y + m_height * 0.7) });
        dc.DrawPolygon(window.size(), window.data());
    }

    void DrawDoor(wxDC& dc)
    {
        std::vector<wxPoint> door;
        door.push_back({ int(m_leftTop.x + m_width * 0.35), int(m_leftTop.y + m_height * 0.7) });
        door.push_back({ int(m_leftTop.x + m_width * 0.45), int(m_leftTop.y + m_height * 0.7) });
        door.push_back({ int(m_leftTop.x + m_width * 0.45), int(m_leftTop.y + m_height * 0.99) });
        door.push_back({ int(m_leftTop.x + m_width * 0.35), int(m_leftTop.y + m_height * 0.99) });
        dc.DrawPolygon(door.size(), door.data());
    }

    void DrawFlue(wxDC& dc)
    {
        std::vector<wxPoint> flue;
        flue.push_back({ int(m_leftTop.x + m_width * 0.4), int(m_leftTop.y + m_height * 0.2) });
        flue.push_back({ int(m_leftTop.x + m_width * 0.45), int(m_leftTop.y + m_height * 0.2) });
        flue.push_back({ int(m_leftTop.x + m_width * 0.45), int(m_leftTop.y + m_height * 0.99) });
        flue.push_back({ int(m_leftTop.x + m_width * 0.4), int(m_leftTop.y + m_height * 0.99) });
        dc.DrawPolygon(flue.size(), flue.data());
    }

    void DrawHouse(wxDC& dc)
    {
        std::vector<wxPoint> house;
        house.push_back({ m_leftTop.x, int(m_leftTop.y + m_height * 0.5) });
        house.push_back({ int(m_leftTop.x + m_width * 0.5), int(m_leftTop.y + m_height * 0.5) });
        house.push_back({ int(m_leftTop.x + m_width * 0.5), m_leftTop.y + m_height });
        house.push_back({ m_leftTop.x, m_leftTop.y + m_height });
        dc.DrawPolygon(house.size(), house.data());
    }

    void DrawFence(wxDC& dc)
    {
        std::vector<wxPoint> fence;
        wxPoint fenceLeftTop = { int(m_leftTop.x + m_width * 0.5), int(m_leftTop.y + m_height * 0.7) };
        wxPoint fenceRightBottom = { m_leftTop.x + m_width, m_leftTop.y + m_height };
        unsigned fencePlankCount = 6;
        int widthFencePlank = (fenceRightBottom.x - fenceLeftTop.x) * 1 / fencePlankCount;
        for (unsigned index = 0; index < fencePlankCount; index++)
        {
            wxPoint leftTop = { int(fenceLeftTop.x + widthFencePlank * index), fenceLeftTop.y };
            wxPoint rightTop = { int(fenceLeftTop.x + widthFencePlank * (index + 1)), fenceLeftTop.y };
            wxPoint rightBottom = { int(fenceLeftTop.x + widthFencePlank * (index + 1)), fenceRightBottom.y };
            wxPoint leftBottom = { int(fenceLeftTop.x + widthFencePlank * index), fenceRightBottom.y };
            if (index == fencePlankCount - 1)
            {
                rightTop = { fenceRightBottom.x, fenceLeftTop.y };
                rightBottom = { fenceRightBottom.x, fenceRightBottom.y };
            }

            fence.push_back(leftTop);
            fence.push_back(rightTop);
            fence.push_back(rightBottom);
            fence.push_back(leftBottom);
            dc.DrawPolygon(fence.size(), fence.data());
            fence.clear();
        }
    }

private:
    wxPoint m_leftTop = { 200, 200 };
    int m_height = 700;
    int m_width = 1000;
};