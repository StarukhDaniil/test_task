#ifndef MYCONSTANTS_H
#define MYCONSTANTS_H

#include <qtypes.h>

namespace myConstants {
inline constexpr int basicMinBtnWidth = 150;
inline constexpr int basicMinBtnHeight = 50;
inline constexpr int basicMaxBtnWidth = 450;
inline constexpr int basicMaxBtnHeight = 150;

inline constexpr int basicMinLineEditWidth = 150;
inline constexpr int basicMinLineEditHeight = 30;
inline constexpr int basicMaxLineEditWidth = 200;
inline constexpr int basicMaxLineEditHeight = 30;

inline constexpr int basicMinLabelWidth = 150;
inline constexpr int basicMinLabelHeight = 30;
inline constexpr int basicMaxLabelWidth = 200;
inline constexpr int basicMaxLabelHeight = 30;

inline constexpr int basicMinListWidth = 150;
inline constexpr int basicMinListHeight = 150;
inline constexpr int basicMaxListWidth = 450;
inline constexpr int basicMaxListHeight = 450;

inline constexpr quint16 requiredVendorIdentifier = 0x04b4;
inline constexpr quint16 requiredProductIdentifier = 0x05;

// length of basic command for controller without parameters
inline constexpr qint16 basicCmdLen = 4;
inline constexpr qint16 BDAddrLen = 6;
}

#endif // MYCONSTANTS_H
