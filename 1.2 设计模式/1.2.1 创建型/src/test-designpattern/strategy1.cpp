enum VacationEnum {
	VAC_Spring,
    VAC_QiXi,
	VAC_Wuyi,
	VAC_GuoQing,
    VAC_ShengDan,
};


// 稳定点  变化点
// 如果一个 只有稳定点  需不需要设计模式
// 如果 全是变化点  怎么办？   c++  游戏开发  脚本语言
class Promotion {
    VacationEnum vac;
public:
    double CalcPromotion(){
        if (vac == VAC_Spring {
            // 春节
        }
        else if (vac == VAC_QiXi) {
            // 七夕
        }
        else if (vac == VAC_Wuyi) {
            // 五一
        }
		else if (vac == VAC_GuoQing) {
			// 国庆
		}
        else if (vac == VAC_ShengDan) {

        }
     }
    
};