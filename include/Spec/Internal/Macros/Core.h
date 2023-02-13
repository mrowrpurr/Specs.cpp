#pragma once

#define __Spec_Macro_Concat_(x, y) x##y
#define __Spec_Macro_Concat(x, y) __Spec_Macro_Concat_(x, y)
#define __Spec_Macro_Unique(count) __Spec_Macro_Concat(__spec_macro_variable__, count)
