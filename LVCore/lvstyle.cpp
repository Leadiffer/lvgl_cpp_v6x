#include "LVStyle.h"

const LVStyle & LVStyle::scr          = *(static_cast<LVStyle*>(&lv_style_scr         )) ;
const LVStyle & LVStyle::transp       = *(static_cast<LVStyle*>(&lv_style_transp      )) ;
const LVStyle & LVStyle::transp_fit   = *(static_cast<LVStyle*>(&lv_style_transp_fit  )) ;
const LVStyle & LVStyle::transp_tight = *(static_cast<LVStyle*>(&lv_style_transp_tight)) ;
const LVStyle & LVStyle::plain        = *(static_cast<LVStyle*>(&lv_style_plain       )) ;
const LVStyle & LVStyle::plain_color  = *(static_cast<LVStyle*>(&lv_style_plain_color )) ;
const LVStyle & LVStyle::pretty       = *(static_cast<LVStyle*>(&lv_style_pretty      )) ;
const LVStyle & LVStyle::pretty_color = *(static_cast<LVStyle*>(&lv_style_pretty_color)) ;
const LVStyle & LVStyle::btn_rel      = *(static_cast<LVStyle*>(&lv_style_btn_rel     )) ;
const LVStyle & LVStyle::btn_pr       = *(static_cast<LVStyle*>(&lv_style_btn_pr      )) ;
const LVStyle & LVStyle::btn_tgl_rel  = *(static_cast<LVStyle*>(&lv_style_btn_tgl_rel )) ;
const LVStyle & LVStyle::btn_tgl_pr   = *(static_cast<LVStyle*>(&lv_style_btn_tgl_pr  )) ;
const LVStyle & LVStyle::btn_ina      = *(static_cast<LVStyle*>(&lv_style_btn_ina     )) ;

LVStyle LVStyle::none = LVStyle::pretty;
