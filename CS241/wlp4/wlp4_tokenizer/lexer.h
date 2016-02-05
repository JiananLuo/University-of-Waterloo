#ifndef __LEXER_H__
#define __LEXER_H__
#include <string>
#include <vector>

namespace ASM{
  // The different states the the MIPS recognizer uses
  // Judicious use of the pimpl idiom or the Bridge pattern
  // would allow us to place this in the implementation file
  // However, that's more complexity than is necessary
    enum State
    {
        ST_ERR,
        ST_ERROR,
        ST_START,
        ST_ID,
        ST_WHITESPACE,
        ST_LPAREN,
        ST_RPAREN,
        ST_LBRACE,
        ST_RBRACE,
        ST_LBRACK,
        ST_RBRACK,
        ST_PLUS,
        ST_MINUS,
        ST_STAR,
        ST_SLASH,
        ST_PCT,
        ST_COMMA,
        ST_SEMI,
        ST_AMP,
        ST_COMMENT,
        ST_LT,
        ST_GT,
        ST_BECOMES,
        ST_NOT,
        ST_LE,
        ST_GE,
        ST_EQ,
        ST_NE,
        ST_ZERO,
        ST_NUM,
        ST_w,
        ST_wa,
        ST_wai,
        ST_wain,
        ST_wh,
        ST_whi,
        ST_whil,
        ST_while,
        ST_i,
        ST_in,
        ST_int,
        ST_if,
        ST_e,
        ST_el,
        ST_els,
        ST_else,
        ST_p,
        ST_pr,
        ST_pri,
        ST_prin,
        ST_print,
        ST_printl,
        ST_println,
        ST_r,
        ST_re,
        ST_ret,
        ST_retu,
        ST_retur,
        ST_return,
        ST_N,
        ST_NU,
        ST_NUL,
        ST_NULL,
        ST_n,
        ST_ne,
        ST_new,
        ST_d,
        ST_de,
        ST_del,
        ST_dele,
        ST_delet,
        ST_delete,
    };
  // Forward declare the Token class to reduce compilation dependencies
  class Token;

  // Class representing a MIPS recognizer
  class Lexer {
    // At most 21 states and 256 transitions (max number of characters in ASCII)
    static const int maxStates = 100;
    static const int maxTrans = 300;
    // Transition function
    State delta[maxStates][maxTrans];
    // Private method to set the transitions based upon characters in the
    // given string
    void setTrans(State from, const std::string& chars, State to);
  public:
    Lexer();
    // Output a vector of Tokens representing the Tokens present in the
    // given line
    std::vector<Token*> scan(const std::string& line);
  };
}

#endif
