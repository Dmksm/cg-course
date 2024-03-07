#pragma once
#include "stdafx.h"

class BufferedBitmap : public wxWindow
{
public:
    BufferedBitmap(
        wxWindow *parent,
        wxWindowID id,
        const wxBitmap& bitmap,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0
    ) : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
    {
        this->SetBackgroundStyle(wxBG_STYLE_PAINT);


        this->Bind(wxEVT_LEFT_DOWN, &BufferedBitmap::OnLeftDown, this);
        this->Bind(wxEVT_LEFT_UP, &BufferedBitmap::OnLeftUp, this);
        this->Bind(wxEVT_MOTION, &BufferedBitmap::OnMouseMove, this);
        this->Bind(wxEVT_PAINT, &BufferedBitmap::OnPaint, this);
        this->Bind(wxEVT_LEAVE_WINDOW, &BufferedBitmap::OnMouseLeave, this);
        this->SetBitmap(bitmap);
    }

    void SetColor(wxColour color)
    {
        m_color = color;
    }

    void OnLeftDown(wxMouseEvent& event)
    {
        m_dots.push_back({});
        m_dragging = true;
    }
    
    void OnMouseLeave(wxMouseEvent& event)
    {
        m_dragging = false;
    }

    void OnLeftUp(wxMouseEvent& event)
    {
        m_dragging = false;
    }

    void OnMouseMove(wxMouseEvent& event)
    {
        if (m_dragging)
        {
            auto pt = event.GetPosition();
            auto& currentSquiggle = m_dots.back();

            currentSquiggle.push_back(pt);
            Refresh();
        }
    }

    void OnPaint(wxPaintEvent& evt)
    {
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();
        wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
            const wxSize bmpSize = m_bitmap.GetSize();
            double w = bmpSize.GetWidth();
            double h = bmpSize.GetHeight();

            const wxSize drawSize = ToDIP(GetClientSize());
            double x = (drawSize.GetWidth() - w) / 2;
            double y = (drawSize.GetHeight() - h) / 2;
            gc->DrawBitmap(m_bitmap, x, y, gc->FromDIP(w), gc->FromDIP(h));

            for (const auto& pointsVector : m_dots)
            {
                if (pointsVector.size() > 1)
                {
                    gc->SetPen(wxPen(m_color, FromDIP(8)));
                    gc->StrokeLines(pointsVector.size(), pointsVector.data());
                }
            }

            delete gc;
        }
    }

    void SaveBitmap()
    {
        wxFileDialog exportFileDialog(this, _("Export drawing"), "", "",
            "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (exportFileDialog.ShowModal() == wxID_CANCEL)
            return;

        wxBitmap bitmap(this->GetSize() * this->GetContentScaleFactor());

        wxMemoryDC memDC;

        memDC.SetUserScale(this->GetContentScaleFactor(), this->GetContentScaleFactor());
        memDC.SelectObject(bitmap);

        wxDC* dc = &memDC;
        dc->SetBackground(*wxBLACK_BRUSH);
        dc->Clear();

        std::unique_ptr<wxGraphicsContext> gc{ wxGraphicsContext::CreateFromUnknownDC(*dc) };

        if (gc)
        {

            const wxSize bmpSize = bitmap.GetSize();
            double w = bmpSize.GetWidth();
            double h = bmpSize.GetHeight();

            const wxSize drawSize = ToDIP(GetClientSize());
            double x = (drawSize.GetWidth() - w) / 2;
            double y = (drawSize.GetHeight() - h) / 2;
            gc->DrawBitmap(bitmap, x, y, gc->FromDIP(w), gc->FromDIP(h));

            for (const auto& pointsVector : m_dots)
            {
                if (pointsVector.size() > 1)
                {
                    gc->SetPen(wxPen(m_color, FromDIP(8)));
                    gc->StrokeLines(pointsVector.size(), pointsVector.data());
                }
            }
        }

        bitmap.SaveFile(exportFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
    }

    void SetBitmap(const wxBitmap& bitmap)
    {
        m_bitmap = bitmap;
        m_dots.clear();
        Refresh();
    }

    const wxBitmap& GetBitmap()
    {
        return m_bitmap;
    }

private:
    wxBitmap m_bitmap;
    wxSize m_size;
    wxColour m_color = wxColour(255ul);

    bool m_dragging = false;
    wxPoint m_pos;
    wxPoint m_dragStartPos;

    std::vector<std::vector<wxPoint2DDouble>> m_dots;
};