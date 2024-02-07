#include "stdafx.h"
#include "CommonTypes.h"

class MyCanvas : public wxPanel 
{
public:
    MyCanvas(wxFrame* parent) : wxPanel(parent)
    {
        SetBackgroundColour(*wxWHITE);
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
        Bind(wxEVT_CHAR_HOOK, &MyCanvas::OnChar, this);
        m_timer.Bind(wxEVT_TIMER, &MyCanvas::OnTimer, this);
        m_timer.Start(50);
    }

    void OnPaint(wxPaintEvent& event) 
    {
        wxPaintDC dc(this);
        Render(dc);
    }

    void OnChar(wxKeyEvent& event) 
    {
        if (event.GetKeyCode() == WXK_ESCAPE) 
        {
            StopAnimation();
        }
        event.Skip();
    }

    void OnTimer(wxTimerEvent& event) 
    {
        UpdateAnimation(m_shape1, m_dy1, m_height);
        UpdateAnimation(m_shape2, m_dy2, m_height);
        UpdateAnimation(m_shape3, m_dy3, m_height);
        Refresh();
    }

    void Render(wxDC& dc) 
    {
        dc.SetBrush(*wxBLUE_BRUSH);
        for (auto point : m_shape1)
        {
            dc.DrawRectangle(point.x, point.y, m_width, m_height);
        }

        dc.SetBrush(*wxYELLOW_BRUSH);
        for (auto point : m_shape2)
        {
            dc.DrawRectangle(point.x, point.y, m_width, m_height);
        }

        dc.SetBrush(*wxRED_BRUSH);
        for (auto point : m_shape3)
        {
            dc.DrawRectangle(point.x, point.y, m_width, m_height);
        }
    }

    void UpdateAnimation(std::vector<PointD>& vertexes, double& dy, double height) 
    {
        if (m_jumping) 
        {
            for (auto& point : vertexes)
            {
                if (point.y <= TOP_LIMIT + dy || point.y + height >= BOTOM_LIMIT + dy)
                {
                    dy = -dy;
                }
                point.y -= dy;
            }
        }
    }

    void StartJumping() 
    {
        m_jumping = true;
    }

    void StopAnimation() 
    {
        m_jumping = false;
    }

private:
    const double TOP_LIMIT = 10;
    const double BOTOM_LIMIT = 1000;
    wxTimer m_timer;
    double m_height = 700;
    double m_width = 100;
    std::vector<PointD> m_shape1 = { {100, 100} };
    std::vector<PointD> m_shape2 = { {500, 100} };
    std::vector<PointD> m_shape3 = { {900, 100} };
    double m_dy1 = 10;
    double m_dy2 = 10.3;
    double m_dy3 = 10.6;
    bool m_jumping = false;
};

class MyFrame : public wxFrame 
{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Animated Home", wxDefaultPosition, wxSize(1920, 1080)) 
    {
        m_canvas = new MyCanvas(this);
        SetBackgroundColour(*wxWHITE);
    }

    void StartAnimation() 
    {
        m_canvas->StartJumping();
    }

private:
    MyCanvas* m_canvas;
};

class MyApp : public wxApp 
{
public:
    bool OnInit() override 
    {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        frame->StartAnimation();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
