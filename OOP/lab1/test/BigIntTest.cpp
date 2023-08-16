#include "gtest/gtest.h"

#include "../src/BigInt.hpp"

TEST(ResTest, ShouldStringBigInt1){
  BigInt a("124314356172");
  EXPECT_EQ(std::string(a), "124314356172");}

TEST(ResTest, ShouldStringBigInt2)
{
  BigInt a("-1124314356172");
  EXPECT_EQ(std::string(a), "-1124314356172");
}

TEST(ResTest, ShouldStringBigInt3)
{
  BigInt a=2000000000;
  EXPECT_EQ(std::string(a), "2000000000");
}

TEST(ResTest, ShouldStringBigInt4)
{
  BigInt a=-2100000000;
  EXPECT_EQ(std::string(a), "-2100000000");
}

TEST(ResTest, ShouldStringBigInt5)
{
  BigInt a("-000000000000000000000000000");
  EXPECT_EQ(std::string(a), "0");
}

TEST(ResTest, ShouldStringBigInt6)
{
  BigInt a=-0;
  EXPECT_EQ(std::string(a), "0");
}

TEST(ResTest, ShouldStringBigInt7)
{
  BigInt a("-00000000000000000000000005454");
  EXPECT_EQ(std::string(a), "-5454");
}

TEST(ResTest, ShouldStringBigInt8)
{
  BigInt a("000000000000000000000000000000000076");
  EXPECT_EQ(std::string(a), "76");
}
TEST(ResTest, ShouldStringBigInt9)
{
  BigInt a("+834778976");
  EXPECT_EQ(std::string(a), "834778976");
}

TEST(ResTest, ShouldSum2BigInt1)
{
	BigInt a=0;
	BigInt b=0;
	EXPECT_EQ(std::string(a+b), "0");
}

TEST(ResTest, ShouldSum2BigInt2)
{
	BigInt a("-1");
	BigInt b("1");
	EXPECT_EQ(std::string((a+b)), "0");
}

TEST(ResTest, ShouldSum2BigInt3)
{
	BigInt a("-156375637453785345");
	BigInt b("156375637453785345");
	EXPECT_EQ(std::string((a+b)), "0");
}

TEST(ResTest, ShouldSum2BigInt4)
{
	BigInt a("354276342534234627");
	BigInt b("63562563272234");
	EXPECT_EQ(std::string((a+b)), "354339905097506861");
}

TEST(ResTest, ShouldSum2BigInt5)
{
	BigInt a("999999999");
	BigInt b=1;
	EXPECT_EQ(std::string((a+b)), "1000000000");
}

TEST(ResTest, ShouldSum2BigInt6)
{
	BigInt a("1000000000");
	BigInt b=-1;
	EXPECT_EQ(std::string((a+b)), "999999999");
}

TEST(ResTest, ShouldSum2BigInt7)
{
	BigInt a("517624512417653761251376");
	BigInt b("-517624512417653761251370");
	EXPECT_EQ(std::string((a+b)), "6");
}

TEST(ResTest, ShouldSum2BigInt8)
{
	BigInt a("-517624512417653761251376");
	BigInt b("51762451241765376125");
	EXPECT_EQ(std::string((a+b)), "-517572749966411995875251");
}

TEST(ResTest, ShouldSum2BigInt9)
{
	BigInt a("-517624512417653761251376");
	BigInt b("-517624512417653761251376");
	EXPECT_EQ(std::string((a+b)), "-1035249024835307522502752");
}

TEST(ResTest, ShouldSum2BigInt10)
{
	BigInt a("-99999999999999999999");
	BigInt b("-1");
	EXPECT_EQ(std::string((a+b)), "-100000000000000000000");
}

TEST(ResTest, ShouldSum2BigInt11)
{
  BigInt a("-234232");
  BigInt b("243724");
  int a1=-234232;
  int b1=243724;
  EXPECT_EQ(static_cast<int>(a+b), a1+b1);
}

TEST(ResTest, ShouldSum2BigInt12)
{
  BigInt a("-234232");
  BigInt b("-243724");
  int a1=-234232;
  int b1=-243724;
  EXPECT_EQ(static_cast<int>(a+b), a1+b1);
}

TEST(ResTest, ShouldSum2BigInt13)
{
  BigInt a("234232");
  BigInt b("243724");
  int a1=234232;
  int b1=243724;
  EXPECT_EQ(static_cast<int>(a+b), a1+b1);
}

TEST(ResTest, ShouldDef2BigInt1)
{
	BigInt a=0;
	BigInt b=0;
	EXPECT_EQ(std::string((a-b)), "0");
}

TEST(ResTest, ShouldDef2BigInt2)
{
	BigInt a("1");
	BigInt b("1");
	EXPECT_EQ(std::string((a-b)), "0");
}

TEST(ResTest, ShouldDef2BigInt3)
{
	BigInt a("999999999");
	BigInt b("-1");
	EXPECT_EQ(std::string((a-b)), "1000000000");
}

TEST(ResTest, ShouldDef2BigInt4)
{
	BigInt a("-1");
	BigInt b("-1");
	EXPECT_EQ(std::string((a-b)), "0");
}

TEST(ResTest, ShouldDef2BigInt5)
{
	BigInt a("5176245124176531251376");
	BigInt b("51762451241765376");
	EXPECT_EQ(std::string((a-b)), "5176193361725289486000");
}

TEST(ResTest, ShouldDef2BigInt6)
{
	BigInt a("-5176245124176578251376");
	BigInt b("-517624451241765376");
	EXPECT_EQ(std::string((a-b)), "-5175727499725336486000");
}

TEST(ResTest, ShouldDef2BigInt7)
{
	BigInt a("12345176246491387942897429634782");
	BigInt b("12345176246491387942897429634782");
	EXPECT_EQ(std::string((a-b)), "0");
}

TEST(ResTest, ShouldDef2BigInt8)
{
	BigInt a("-38748226223142");
	BigInt b("-38748226223142");
	EXPECT_EQ(std::string((a-b)), "0");
}

TEST(ResTest, ShouldDef2BigInt9)
{
	BigInt a("100000000000000000000000");
	BigInt b("1");
	EXPECT_EQ(std::string((a-b)), "99999999999999999999999");
}

TEST(ResTest, ShouldDef2BigInt10)
{
	BigInt a("-99999999999999999999999");
	BigInt b("1");
	EXPECT_EQ(std::string((a-b)), "-100000000000000000000000");
}

TEST(ResTest, ShouldDef2BigInt11)
{
  BigInt a("234232");
  BigInt b("243724");
  int a1=234232;
  int b1=243724;
  EXPECT_EQ(static_cast<int>(a-b), a1-b1);
}

TEST(ResTest, ShouldDef2BigInt12)
{
  BigInt a("-234232");
  BigInt b("243724");
  int a1=-234232;
  int b1=243724;
  EXPECT_EQ(static_cast<int>(a-b), a1-b1);
}

TEST(ResTest, ShouldDef2BigInt13)
{
  BigInt a("-234232");
  BigInt b("-243724");
  int a1=-234232;
  int b1=-243724;
  EXPECT_EQ(static_cast<int>(a-b), a1-b1);
}

TEST(ResTest, ShouldMul2BigInt1)
{
	BigInt a=0;
	BigInt b=0;
	EXPECT_EQ(std::string((a*b)), "0");
}

TEST(ResTest, ShouldMul2BigInt2)
{
	BigInt a("0");
	BigInt b("1");
	EXPECT_EQ(std::string((a*b)), "0");
}

TEST(ResTest, ShouldMul2BigInt3)
{
	BigInt a("0");
	BigInt b("-32672637562652763542652763427");
	EXPECT_EQ(std::string((a*b)), "0");
}

TEST(ResTest, ShouldMul2BigInt4)
{
	BigInt a("42334241");
	BigInt b("-32672637562652763542652763427");
	EXPECT_EQ(std::string((a*b)), "-1383171312682994691130675866234603907");
}

TEST(ResTest, ShouldMul2BigInt5)
{
	BigInt a("21341429009821");
	BigInt b("32672637562652763542652763427");
	EXPECT_EQ(std::string((a*b)), "697280775106964978302125213083509972616567");
}

TEST(ResTest, ShouldMul2BigInt6)
{
	BigInt a("-121125666");
	BigInt b("-8881236123422");
	EXPECT_EQ(std::string((a*b)), "1075745640352747949052");
}

TEST(ResTest, ShouldMul2BigInt7)
{
  BigInt a("999999999999999999999999999");
  BigInt b("999999999999999999999999999");
  EXPECT_EQ(std::string((a*b)), "999999999999999999999999998000000000000000000000000001");
}

TEST(ResTest, ShouldMul2BigInt8)
{
	BigInt a("0");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a*b)), "0");
}

TEST(ResTest, ShouldMul2BigInt9)
{
  BigInt a("34232");
  BigInt b("43724");
  int a1=34232;
  int b1=43724;
  EXPECT_EQ(static_cast<int>(a*b), a1*b1);
}

TEST(ResTest, ShouldMul2BigInt10)
{
  BigInt a("-34232");
  BigInt b("43724");
  int a1=-34232;
  int b1=43724;
  EXPECT_EQ(static_cast<int>(a*b), a1*b1);
}

TEST(ResTest, ShouldMul2BigInt11)
{
  BigInt a("-34232");
  BigInt b("-43724");
  int a1=-34232;
  int b1=-43724;
  EXPECT_EQ(static_cast<int>(a*b), a1*b1);
}

TEST(ResTest, ShouldDiv2BigInt1)
{
	BigInt a=0;
	BigInt b=1;
	EXPECT_EQ(std::string((a/b)), "0");
}

TEST(ResTest, ShouldDiv2BigInt2)
{
	BigInt a("0");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a/b)), "0");
}

TEST(ResTest, ShouldDiv2BigInt3)
{
	BigInt a("-253462564");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a/b)), "0");
}

TEST(ResTest, ShouldDiv2BigInt4)
{
	BigInt a("-256745276452654275428772936472934672348");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a/b)), "-256745276");
}

TEST(ResTest, ShouldDiv2BigInt5)
{
	BigInt a("-1");
	BigInt b("1");
	EXPECT_EQ(std::string((a/b)), "-1");
}

TEST(ResTest, ShouldDiv2BigInt6)
{
	BigInt a("-124351425631462351");
	BigInt b("-24356478");
	EXPECT_EQ(std::string((a/b)), "5105476482");
}

TEST(ResTest, ShouldDiv2BigInt7)
{
	BigInt a("9999999999999999999999");
	BigInt b("99");
	EXPECT_EQ(std::string((a/b)), "101010101010101010101");
}

TEST(ResTest, ShouldDiv2BigInt8)
{
  BigInt a("23400232");
  BigInt b("244");
  int a1=23400232;
  int b1=244;
  EXPECT_EQ(static_cast<int>(a/b), a1/b1);
}

TEST(ResTest, ShouldDiv2BigInt9)
{
  BigInt a("13423662");
  BigInt b("-2454");
  int a1=13423662;
  int b1=-2454;
  EXPECT_EQ(static_cast<int>(a/b), a1/b1);
}

TEST(ResTest, ShouldDiv2BigInt10)
{
  BigInt a("-2342372");
  BigInt b("-2544");
  int a1=-2342372;
  int b1=-2544;
  EXPECT_EQ(static_cast<int>(a/b), a1/b1);
}

TEST(ResTest, ShouldRem2BigInt1)
{
	BigInt a=0;
	BigInt b=1;
	EXPECT_EQ(std::string((a%b)), "0");
}

TEST(ResTest, ShouldRem2BigInt2)
{
	BigInt a("0");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a%b)), "0");
}

TEST(ResTest, ShouldRem2BigInt3)
{
	BigInt a("-253462564");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a%b)), "999999999999999991729118511253");
}

TEST(ResTest, ShouldRem2BigInt4)
{
	BigInt a("-256745276452654275428772936472934672348");
	BigInt b("999999999999999991729371973817");
	EXPECT_EQ(std::string((a%b)), "547345722447782379980747739961");
}

TEST(ResTest, ShouldRem2BigInt5)
{
	BigInt a("-1");
	BigInt b("1");
	EXPECT_EQ(std::string((a%b)), "0");
}

TEST(ResTest, ShouldRem2BigInt6)
{
	BigInt a("-124351425631462351");
	BigInt b("-24356478");
	EXPECT_EQ(std::string((a%b)), "6244523");
}

TEST(ResTest, ShouldRem2BigInt7)
{
	BigInt a("1243514256314623");
	BigInt b("-24356478");
	EXPECT_EQ(std::string((a%b)), "20153431");
}

TEST(ResTest, ShouldRem2BigInt8)
{
	BigInt a("9999999999999999999999");
	BigInt b("99");
	EXPECT_EQ(std::string((a%b)), "0");
}

TEST(ResTest, ShouldRem2BigInt9)
{
  BigInt a("23400232");
  BigInt b("244");
  int a1=23400232;
  int b1=244;
  EXPECT_EQ(static_cast<int>(a%b), a1%b1);
}

TEST(ResTest, ShouldRem2BigInt10)
{
  BigInt a("2340022");
  BigInt b("2477");
  int a1=2340022;
  int b1=2477;
  EXPECT_EQ(static_cast<int>(a%b), a1%b1);
}

TEST(ResTest, ShouldRem2BigInt11)
{
  BigInt a("12321324");
  BigInt b("744");
  int a1=12321324;
  int b1=744;
  EXPECT_EQ(static_cast<int>(a%b), a1%b1);
}

TEST(ResTest, ShouldAnd2BigInt1)
{
	BigInt a("-126317661535714");
	BigInt b("126315265162536671562");
	EXPECT_EQ(std::string(a&b), "126315141595887157258");
}

TEST(ResTest, ShouldAnd2BigInt2)
{
	BigInt a("-12631766135736748535714");
	BigInt b("9982738428382342948242492938282");
	EXPECT_EQ(std::string(a&b), "9982738427639550732862186721290");
}

TEST(ResTest, ShouldAnd2BigInt3)
{
  BigInt a("0");
  BigInt b("9982738428382342948242492938282");
  EXPECT_EQ(std::string(a&b), "0");
}

TEST(ResTest, ShouldAnd2BigInt4)
{
  BigInt a("-1");
  BigInt b("9982738428382342948242492938282");
  EXPECT_EQ(std::string(a&b), "9982738428382342948242492938282");
}

TEST(ResTest, ShouldAnd2BigInt5)
{
  BigInt a("76");
  BigInt b("9982738428125352642948242492938282");
  EXPECT_EQ(std::string(a&b), "8");
}

TEST(ResTest, ShouldAnd2BigInt6)
{
  BigInt a("2873647263482374256346264");
  BigInt b("-11");
  EXPECT_EQ(std::string(a&b), "2873647263482374256346256");
}

TEST(ResTest, ShouldAnd2BigInt7)
{
  BigInt a("12321324");
  BigInt b("744");
  int a1=12321324;
  int b1=744;
  EXPECT_EQ(static_cast<int>(a&b), a1&b1);
}

TEST(ResTest, ShouldAnd2BigInt8)
{
  BigInt a("-12321324");
  BigInt b("744");
  int a1=-12321324;
  int b1=744;
  EXPECT_EQ(static_cast<int>(a&b), a1&b1);
}

TEST(ResTest, ShouldAnd2BigInt9)
{
  BigInt a("-12321324");
  BigInt b("-744");
  int a1=-12321324;
  int b1=-744;
  EXPECT_EQ(static_cast<int>(a&b), a1&b1);
}

TEST(ResTest, ShouldOr2BigInt1)
{
  BigInt a("-12631766135736748535714");
  BigInt b("9982738428382342948242492938282");
  EXPECT_EQ(std::string(a|b), "-11888973920356442318722");
}

TEST(ResTest, ShouldOr2BigInt2)
{
  BigInt a("-1");
  BigInt b("9982738428382342948242492938282");
  EXPECT_EQ(std::string(a|b), "-1");
}

TEST(ResTest, ShouldOr2BigInt3)
{
  BigInt a("-1243541");
  BigInt b("-2863772673712");
  EXPECT_EQ(std::string(a|b), "-139397");
}

TEST(ResTest, ShouldOr2BigInt4)
{
  BigInt a("-278900009388278342");
  BigInt b("0");
  EXPECT_EQ(std::string(a|b), "-278900009388278342");
}

TEST(ResTest, ShouldOr2BigInt5)
{
  BigInt a("12321324");
  BigInt b("744");
  int a1=12321324;
  int b1=744;
  EXPECT_EQ(static_cast<int>(a|b), a1|b1);
}

TEST(ResTest, ShouldOr2BigInt6)
{
  BigInt a("-12321324");
  BigInt b("744");
  int a1=-12321324;
  int b1=744;
  EXPECT_EQ(static_cast<int>(a|b), a1|b1);
}

TEST(ResTest, ShouldOr2BigInt7)
{
  BigInt a("-12321324");
  BigInt b("-744");
  int a1=-12321324;
  int b1=-744;
  EXPECT_EQ(static_cast<int>(a|b), a1|b1);
}

TEST(ResTest, ShouldXor2BigInt1)
{
  BigInt a("-12631766135736748535714");
  BigInt b("9982738428382342948242492938282");
  EXPECT_EQ(std::string(a^b), "-9982738439528524653218629040012");
}

TEST(ResTest, ShouldXor2BigInt2)
{
  BigInt a("-1243541");
  BigInt b("-2863772673712");
  EXPECT_EQ(std::string(a^b), "2863773638459");
}

TEST(ResTest, ShouldXor2BigInt3)
{
  BigInt a("-12631766135736748535714");
  BigInt b("-12631766135736748535714");
  EXPECT_EQ(std::string(a^b), "0");
}

TEST(ResTest, ShouldXor2BigInt4)
{
  BigInt a("-1");
  BigInt b("0");
  EXPECT_EQ(std::string(a^b), "-1");
}

TEST(ResTest, ShouldXor2BigInt5)
{
  BigInt a("-1278364782634782678");
  BigInt b("56");
  EXPECT_EQ(std::string(a^b), "-1278364782634782702");
}

TEST(ResTest, ShouldXor2BigInt6)
{
  BigInt a("-23");
  BigInt b("5628947587295849");
  EXPECT_EQ(std::string(a^b), "-5628947587295872");
}

TEST(ResTest, ShouldXor2BigInt7)
{
  BigInt a("-12321324");
  BigInt b("-744");
  int a1=-12321324;
  int b1=-744;
  EXPECT_EQ(static_cast<int>(a^b), a1^b1);
}

TEST(ResTest, ShouldXor2BigInt8)
{
  BigInt a("12321324");
  BigInt b("744");
  int a1=12321324;
  int b1=744;
  EXPECT_EQ(static_cast<int>(a^b), a1^b1);
}

TEST(ResTest, ShouldXor2BigInt9)
{
  BigInt a("12321324");
  BigInt b("-744");
  int a1=12321324;
  int b1=-744;
  EXPECT_EQ(static_cast<int>(a^b), a1^b1);
}

TEST(ResTest, ShouldInvers2BigInt1)
{
  BigInt a("-23");
  EXPECT_EQ(std::string(~a), "22");
}

TEST(ResTest, ShouldInvers2BigInt2)
{
  BigInt a("-1");
  EXPECT_EQ(std::string(~a), "0");
}

TEST(ResTest, ShouldInvers2BigInt3)
{
  BigInt a("0");
  EXPECT_EQ(std::string(~a), "-1");
}

TEST(ResTest, ShouldInvers2BigInt4)
{
  BigInt a("-7235643742");
  EXPECT_EQ(std::string(~a), "7235643741");
}

TEST(ResTest, ShouldInvers2BigInt5)
{
  BigInt a("56234527547253427");
  EXPECT_EQ(std::string(~a), "-56234527547253428");
}

TEST(BigIntTest, ShouldInvers2BigInt6)
{
int expected_result = -173684;
BigInt a("-173684");
EXPECT_EQ(static_cast<int>(~a), ~expected_result);
}

TEST(BigIntTest, ShouldInvers2BigInt7)
{
int expected_result = 173684;
BigInt a("173684");
EXPECT_EQ(static_cast<int>(~a), ~expected_result);
}

TEST(ResTest, ShouldNotEqualBigInt1)
{
  BigInt a("0");
  BigInt b("0");
  EXPECT_EQ((a!=b), 0);
}

TEST(ResTest, ShouldNotEqualBigInt2)
{
  BigInt a("999999999999");
  BigInt b("999999989999");
  EXPECT_EQ((a!=b), 1);
}

TEST(ResTest, ShouldNotEqualBigInt3)
{
  BigInt a("-1");
  BigInt b("1");
  EXPECT_EQ((a!=b), 1);
}

TEST(ResTest, ShouldNotEqualBigInt4)
{
  BigInt a("28647237643");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a!=b), 1);
}

TEST(ResTest, ShouldNotEqualBigInt5)
{
  BigInt a("276352667243532763427642376");
  BigInt b("512376423764527624");
  EXPECT_EQ((a!=b), 1);
}

TEST(ResTest, ShouldLessOrEqualBigInt1)
{
  BigInt a("276352667243532763427642376");
  BigInt b("512376423764527624");
  EXPECT_EQ((a<=b), 0);
}

TEST(ResTest, ShouldLessOrEqualBigInt2)
{
  BigInt a("-225354334634343453453");
  BigInt b("512376423764527624");
  EXPECT_EQ((a<=b), 1);
}

TEST(ResTest, ShouldLessOrEqualBigInt3)
{
  BigInt a("-225354334634343453453");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a<=b), 1);
}

TEST(ResTest, ShouldLessOrEqualBigInt4)
{
  BigInt a("-225354453453");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a<=b), 0);
}

TEST(ResTest, ShouldLessOrEqualBigInt5)
{
  BigInt a("225354453453");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a<=b), 0);
}

TEST(ResTest, ShouldLessOrEqualBigInt6)
{
  BigInt a("0");
  BigInt b("0");
  EXPECT_EQ((a<=b), 1);
}

TEST(ResTest, ShouldLessOrEqualBigInt7)
{
  BigInt a("-24552345564566");
  BigInt b("-24552345564566");
  EXPECT_EQ((a<=b), 1);
}

TEST(ResTest, ShouldLessOrEqualBigInt8)
{
  BigInt a("8487745345564566");
  BigInt b("8487745345564566");
  EXPECT_EQ((a<=b), 1);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt1)
{
  BigInt a("276352667243532763427642376");
  BigInt b("512376423764527624");
  EXPECT_EQ((a>=b), 1);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt2)
{
  BigInt a("-225354334634343453453");
  BigInt b("512376423764527624");
  EXPECT_EQ((a>=b), 0);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt3)
{
  BigInt a("-225354334634343453453");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a>=b), 0);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt4)
{
  BigInt a("-225354453453");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a>=b), 1);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt5)
{
  BigInt a("225354453453");
  BigInt b("-512376423764527624");
  EXPECT_EQ((a>=b), 1);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt6)
{
  BigInt a("0");
  BigInt b("0");
  EXPECT_EQ((a>=b), 1);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt7)
{
  BigInt a("-24552345564566");
  BigInt b("-24552345564566");
  EXPECT_EQ((a>=b), 1);
}

TEST(ResTest, ShouldGreaterOrEqualBigInt8)
{
  BigInt a("8487745345564566");
  BigInt b("8487745345564566");
  EXPECT_EQ((a>=b), 1);
}

TEST(ResTest, ShouldUnaruPlusBigInt1)
{
  BigInt a("848774534362745564566");
  BigInt b=(+a);
  EXPECT_EQ(std::string(b), std::string(a));
}

TEST(ResTest, ShouldPreIncBigInt1)
{
  BigInt a("848774534362745564566");
  BigInt b=++a;
  EXPECT_EQ(std::string(b), "848774534362745564567");
}

TEST(ResTest, ShouldPreIncBigInt2)
{
  BigInt a("-1");
  BigInt b=++a;
  EXPECT_EQ(std::string(b), "0");
}

TEST(ResTest, ShouldPreIncBigInt3)
{
  BigInt a("-1000000000");
  BigInt b=++a;
  EXPECT_EQ(std::string(b), "-999999999");
}

TEST(ResTest, ShouldPreIncBigInt4)
{
  BigInt a("999999999");
  BigInt b=++a;
  EXPECT_EQ(std::string(b), "1000000000");
}

TEST(ResTest, ShouldPostIncBigInt1)
{
  BigInt a("999999999");
  BigInt b=a++;
  EXPECT_EQ(std::string(b), std::string(b));
}

TEST(ResTest, ShouldPreDecBigInt1)
{
  BigInt a("848774534362745564566");
  BigInt b=--a;
  EXPECT_EQ(std::string(b), "848774534362745564565");
}

TEST(ResTest, ShouldPreDecBigInt2)
{
  BigInt a("1");
  BigInt b=--a;
  EXPECT_EQ(std::string(b), "0");
}

TEST(ResTest, ShouldPreDecBigInt3)
{
  BigInt a("-999999999");
  BigInt b=--a;
  EXPECT_EQ(std::string(b), "-1000000000");
}

TEST(ResTest, ShouldPreDecBigInt4)
{
  BigInt a("1000000000");
  BigInt b=--a;
  EXPECT_EQ(std::string(b), "999999999");
}

TEST(ResTest, ShouldPostDecBigInt1)
{
  BigInt a("999999999");
  BigInt b=a--;
  EXPECT_EQ(std::string(b), std::string(b));
}

TEST(ResTest, ShouldSizeBigInt1)
{
  BigInt a("999999999");
  EXPECT_EQ(a.size(), 1);
}

TEST(ResTest, ShouldSizeBigInt2)
{
  BigInt a("1000000000");
  EXPECT_EQ(a.size(), 2);
}

TEST(ResTest, ShouldSizeBigInt3)
{
  BigInt a=-2100000000;
  EXPECT_EQ(a.size(), 2);
}

TEST(ResTest, ShouldSizeBigInt4)
{
  BigInt a("14253451235614534112342");
  EXPECT_EQ(a.size(), 3);
}

TEST(ResTest, ShouldSizeBigInt5)
{
  BigInt a("14253451235614534112342");
  BigInt b("14253451235614534112342");
  a-=b;
  EXPECT_EQ(a.size(), 1);
}

TEST(ResTest, ShouldIntBigInt1)
{
  BigInt a("14253451235614534112342");
  EXPECT_EQ(int(a), 534112342);
}

TEST(ResTest, ShouldIntBigInt2)
{
  BigInt a("14253451235611534112342");
  EXPECT_EQ(int(a), 1534112342);
}

TEST(ResTest, ShouldIntBigInt3)
{
  BigInt a("-14253451235611534112342");
  EXPECT_EQ(int(a), -1534112342);
}

TEST(ResTest, ShouldIntBigInt4)
{
  BigInt a("-9999");
  EXPECT_EQ(int(a), -9999);
}

TEST(ResTest, ShouldIntBigInt5)
{
  BigInt a("-14253451235612534112342");
  EXPECT_EQ(int(a), -534112342);
}

TEST(ResTest, ShouldOStreamBigInt1)
{
  BigInt a("-14253451235612534112342");
  std::ostringstream s;
  s<<a;
  EXPECT_EQ(s.str(),  "-14253451235612534112342");
}

TEST(ResTest, ShouldInvArgDivBigInt1)
{
  BigInt a("14253451235614534112342");
  BigInt b("0");
  EXPECT_THROW((a/b),  std::invalid_argument);
}

TEST(ResTest, ShouldInvArgRemBigInt1)
{
  BigInt a("14253451235614534112342");
  BigInt b("0");
  EXPECT_THROW((a%b),  std::invalid_argument);
}

TEST(ResTest, ShouldInvArgConstrBigInt1)
{
  EXPECT_THROW(BigInt a("1425345i1235614534112342"),  std::invalid_argument);
}
