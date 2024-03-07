#pragma once
#include "stdafx.h"

class OpacityDialog : public wxDialog
{
public:
    OpacityDialog(
        wxWindow *parent,
        wxWindowID id = wxID_ANY,
        const wxString &title = "Opacity",
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE
    ) : wxDialog(parent, id, title, pos, size, style)
    {
        m_slider = new wxSlider(this, wxID_ANY, 255, 0, 255);
        m_label = new wxStaticText(this, wxID_ANY, "Alpha: 255");

        m_slider->Bind(wxEVT_SLIDER, &OpacityDialog::OnSliderChanged, this);

        auto sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(m_slider, 0, wxEXPAND | wxALL, FromDIP(20));
        sizer->Add(m_label, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, FromDIP(20));
        sizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxALL, FromDIP(10));

        this->SetSizerAndFit(sizer);
    }

    int GetSelectedOpacity() const 
    { 
        return m_slider->GetValue(); 
    }

private:
    wxSlider *m_slider;
    wxStaticText *m_label;

    void OnSliderChanged(wxCommandEvent& event)
    {
        m_label->SetLabel(wxString::Format("Alpha: %i", event.GetInt()));
    }
};