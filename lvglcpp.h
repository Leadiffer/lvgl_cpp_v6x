
#ifndef __LVGL_CPP_H__
#define __LVGL_CPP_H__

#include <stdlib.h>
#include <stdio.h>


//图形库封装规则约束
//1.尽量不改动名称
//2.对缩写进行补全
//3.尽量使用C++语法
//4.全局枚举用类中枚举封装,或者枚举类封装,但是简化名称 LV_
//5.属性获取 getXxxxx()
//6.属性设置 setXxxxx()

// 封装计划
// 第一步转化所有c函数到C++函数
// 第二步添加增强功能
// 第三步添加自定义对象
// 第四部利用C++重实现lvgl库


//定义用户数据指针类型
//typedef struct _user_data_ptr
//{
//    uintptr_t pointer:(sizeof(uintptr_t)-1); //!< 数据地址
//    uintptr_t deleted:1; //!< 数据是否有效
//} user_data_ptr;

#ifdef __cplusplus
extern "C"
{
#endif

bool lv_cpp_obj_init ();
bool lv_cpp_group_init();
bool lv_cpp_task_init();
bool lv_cpp_anim_init();

#ifdef __cplusplus
}
#endif

/////////LVCore///////////////
#include "LVCore/LVCallBack.h"
#include "LVCore/LVNoCopy.h"
#include "LVCore/LVPointer.h"
#include "LVCore/LVSignal.h"
#include "LVCore/LVSignalSlot.h"
#include "LVCore/LVSlot.h"
#include "LVCore/LVDispaly.h"
#include "LVCore/LVGroup.h"
#include "LVCore/LVInputDevice.h"
#include "LVCore/LVObject.h"
#include "LVCore/LVRefresh.h"
#include "LVCore/LVStyle.h"


////////////LVThemes//////////////
#include "LVThemes/LVTheme.h"
#include "LVThemes/LVThemeAlien.h"
#include "LVThemes/LVThemeDefault.h"
#include "LVThemes/LVThemeMaterial.h"
#include "LVThemes/LVThemeMono.h"
#include "LVThemes/LVThemeNemo.h"
#include "LVThemes/LVThemeNight.h"
#include "LVThemes/LVThemeTempl.h"
#include "LVThemes/LVThemeZen.h"


//////////LVDraw////////////////
//#include "LVDraw/lv_draw.h"
//#include "LVDraw/lv_draw_arc.h"
//#include "LVDraw/lv_draw_basic.h"
//#include "LVDraw/lv_draw_img.h"
//#include "LVDraw/lv_draw_label.h"
//#include "LVDraw/lv_draw_line.h"
//#include "LVDraw/lv_draw_rect.h"
//#include "LVDraw/lv_draw_triangle.h"
//#include "LVDraw/lv_img_decoder.h"


//////////LVFonts///////////////
#include "LVFonts/LVSymbol.h"
#include "LVFonts/LVFont.h"


//////////LVHal////////////////
#include "LVHal/LVHal.h"
#include "LVHal/LVHalDisplayDirver.h"
#include "LVHal/LVHalInputDirver.h"
#include "LVHal/LVHalTick.h"


///////////LVMisc//////////////
#include "LVMisc/LVString.h"
#include "LVMisc/LVTypes.h"
#include "LVMisc/LVAnimation.h"
#include "LVMisc/LVArea.h"
#include "LVMisc/LVColor.h"
#include "LVMisc/LVFileSystem.h"
#include "LVMisc/LVLinkList.h"
#include "LVMisc/LVLog.h"
#include "LVMisc/LVMath.h"
#include "LVMisc/LVMemory.h"
#include "LVMisc/LVTask.h"
#include "LVMisc/LVText.h"
#include "LVMisc/LVUtils.h"


///////////LVObjx/////////////
#include "LVObjx/LVArc.h"
#include "LVObjx/LVBar.h"
#include "LVObjx/LVButton.h"
#include "LVObjx/LVButtonExt.h"
#include "LVObjx/LVButtonMatrix.h"
#include "LVObjx/LVCalendar.h"
#include "LVObjx/LVCanvas.h"
#include "LVObjx/LVChart.h"
#include "LVObjx/LVCheckBox.h"
#include "LVObjx/LVContainer.h"
#include "LVObjx/LVDropDownList.h"
#include "LVObjx/LVGauge.h"
#include "LVObjx/LVImage.h"
#include "LVObjx/LVImageButton.h"
#include "LVObjx/LVKeyBoard.h"
#include "LVObjx/LVLabel.h"
#include "LVObjx/LVLed.h"
#include "LVObjx/LVLine.h"
#include "LVObjx/LVLineMeter.h"
#include "LVObjx/LVList.h"
#include "LVObjx/LVMessageBox.h"
#include "LVObjx/LVPage.h"
#include "LVObjx/LVPreloader.h"
#include "LVObjx/LVRoller.h"
#include "LVObjx/LVSlider.h"
#include "LVObjx/LVSpinBox.h"
#include "LVObjx/LVSwitch.h"
#include "LVObjx/LVTabView.h"
#include "LVObjx/LVTable.h"
#include "LVObjx/LVTextArea.h"
#include "LVObjx/LVTileView.h"
#include "LVObjx/LVWindow.h"

#endif //__LVGL_CPP_H__
