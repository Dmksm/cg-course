#include "stdafx.h"

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
        UpdateAnimation(m_shape1, m_dy1);
        UpdateAnimation(m_shape2, m_dy2);
        UpdateAnimation(m_shape3, m_dy3);
        Refresh();
    }

    void Render(wxDC& dc) 
    {
        dc.SetBrush(*wxBLUE_BRUSH);
        dc.DrawPolygon(m_shape1.size(), m_shape1.data());

        dc.SetBrush(*wxYELLOW_BRUSH);
        dc.DrawPolygon(m_shape2.size(), m_shape2.data());

        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawPolygon(m_shape3.size(), m_shape3.data());
    }

    void UpdateAnimation(std::vector<wxPoint>& shape, double& dy)
    {
        if (m_jumping) 
        {
            bool isOutOfBorder = false;
            for (auto& point : shape)
            {
                if (point.y <= TOP_LIMIT + dy || point.y >= BOTOM_LIMIT + dy)
                {
                    isOutOfBorder = true;
                }
                point.y -= dy;
            }
            if (isOutOfBorder)
            {
                dy = -dy;
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
    std::vector<wxPoint> m_shape1 = {
        {100, 100}, {200, 100}, {200, 300}, {300, 300}, {300, 100},
        {400, 100}, {400, 800}, {300, 800}, {300, 400}, {100, 400},
    };
    std::vector<wxPoint> m_shape2 = {
        {500, 100}, {600, 100}, {700, 400}, {800, 100}, {900, 100}, {900, 800},
        {800, 800}, {800, 300}, {700, 600}, {600, 300}, {600, 800}, {500, 800},
    };
    std::vector<wxPoint> m_shape3 = {
        {1000, 100}, {1300, 100}, {1300, 400}, {1400, 400},
        {1400, 800}, {1000, 800}, {1000, 100}, {1100, 200},
        {1200, 200}, {1200, 400}, {1100, 400}, {1100, 500},
        {1300, 500}, {1300, 700}, {1100, 700}, {1100, 200}
    };
    double m_dy1 = 10;
    double m_dy2 = 11;
    double m_dy3 = 11.3;
    bool m_jumping = false;
};

class MyFrame : public wxFrame 
{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Animated Initials", wxDefaultPosition, wxSize(1920, 1080)) 
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
