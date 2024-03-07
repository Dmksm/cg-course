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
        this->SetBitmap(bitmap);
    }

    void OnLeftDown(wxMouseEvent& event)
    {
        m_dragStartPos = event.GetPosition();
        m_dragging = true;
    }

    void OnLeftUp(wxMouseEvent& event)
    {
        m_dragging = false;
    }

    void OnMouseMove(wxMouseEvent& event)
    {
        if (m_dragging)
        {
            wxPoint delta = event.GetPosition() - m_dragStartPos;
            const wxSize bmpSize = m_bitmap.GetSize();
            const wxSize drawSize = ToDIP(GetClientSize());

            double w = bmpSize.GetWidth();
            m_pos += delta;
            if (m_pos.x > drawSize.GetWidth() - w)
            {
                m_pos.x = drawSize.GetWidth() - w;
            }
            if (m_pos.x < 0)
            {
                m_pos.x = 0;
            }

            double h = bmpSize.GetHeight();
            if (m_pos.y > drawSize.GetHeight() - h)
            {
                m_pos.y = drawSize.GetHeight() - h;
            }
            if (m_pos.y < 0)
            {
                m_pos.y = 0;
            }
            Refresh();
            m_dragStartPos = event.GetPosition();
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

            gc->DrawBitmap(m_bitmap, gc->FromDIP(m_pos.x), gc->FromDIP(m_pos.y), gc->FromDIP(w), gc->FromDIP(h));

            delete gc;
        }
    }

    void SetBitmap(const wxBitmap& bitmap)
    {
        m_bitmap = bitmap;
        Refresh();
    }

    const wxBitmap& GetBitmap()
    {
        return m_bitmap;
    }

private:
    wxBitmap m_bitmap;
    wxSize m_size;

    bool m_dragging = false;
    wxPoint m_pos;
    wxPoint m_dragStartPos;
};