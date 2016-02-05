#include "lexer.h"
#include "kind.h"
using std::string;
using std::vector;

// Use the annonymous namespace to prevent external linking
namespace {
    // An array represents the Token kind that each state represents
    // The ERR Kind represents an invalid token
    ASM::Kind stateKinds[] =
    {
        
        ASM::ERR,			// eRR
        ASM::ERR,			// START
        ASM::ERR,
        ASM::ID,
        ASM::WHITESPACE,
        ASM::LPAREN,
        ASM::RPAREN,
        ASM::LBRACE,
        ASM::RBRACE,
        ASM::LBRACK,
        ASM::RBRACK,
        ASM::PLUS,
        ASM::MINUS,
        ASM::STAR,
        ASM::SLASH,
        ASM::PCT,
        ASM::COMMA,
        ASM::SEMI,
        ASM::AMP,
        ASM::WHITESPACE,
        ASM::LT,
        ASM::GT,
        ASM::BECOMES,
        ASM::ERR,
        ASM::LE,
        ASM::GE,
        ASM::EQ,
        ASM::NE,
        ASM::NUM,
        ASM::NUM,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::WAIN,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::WHILE,
        ASM::ID,
        ASM::ID,
        ASM::INT,
        ASM::IF,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ELSE,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::PRINTLN,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::RETURNN,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::NULLL,
        ASM::ID,
        ASM::ID,
        ASM::NEW,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::ID,
        ASM::DELETE,
    };
    const string whitespace = "\t\n\r ";
    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const string digits = "0123456789";
    const string oneToNine =  "123456789";
    
}

ASM::Lexer::Lexer(){
    // Set default transitions to the Error state
    for(int i=0; i < maxStates; ++i){
        for(int j=0; j < maxTrans; ++j){
            delta[i][j] = ST_ERR;
        }
    }
    // Change transitions as appropriate for the MIPS recognizer
    
    setTrans( ST_START,		letters,		ST_ID			);
    setTrans( ST_ID,		letters+digits,	ST_ID			);
    setTrans( ST_w,			letters+digits,	ST_ID			);
    setTrans( ST_wa,		letters+digits,	ST_ID			);
    setTrans( ST_wai,		letters+digits,	ST_ID			);
    setTrans( ST_wain,		letters+digits,	ST_ID			);
    setTrans( ST_wh,		letters+digits,	ST_ID			);
    setTrans( ST_whi,		letters+digits,	ST_ID			);
    setTrans( ST_whil,		letters+digits,	ST_ID			);
    setTrans( ST_while,		letters+digits,	ST_ID			);
    setTrans( ST_i,			letters+digits,	ST_ID			);
    setTrans( ST_in,		letters+digits,	ST_ID			);
    setTrans( ST_int,		letters+digits,	ST_ID			);
    setTrans( ST_if,		letters+digits,	ST_ID			);
    setTrans( ST_e,			letters+digits,	ST_ID			);
    setTrans( ST_el,		letters+digits,	ST_ID			);
    setTrans( ST_els,		letters+digits,	ST_ID			);
    setTrans( ST_else,		letters+digits,	ST_ID			);
    setTrans( ST_START,		whitespace,		ST_WHITESPACE	);
    setTrans( ST_WHITESPACE,whitespace,		ST_WHITESPACE	);
    setTrans( ST_p,			letters+digits,	ST_ID			);
    setTrans( ST_pr,		letters+digits,	ST_ID			);
    setTrans( ST_pri,		letters+digits,	ST_ID			);
    setTrans( ST_prin,		letters+digits,	ST_ID			);
    setTrans( ST_print,		letters+digits,	ST_ID			);
    setTrans( ST_printl,	letters+digits,	ST_ID			);
    setTrans( ST_println,	letters+digits,	ST_ID			);
    setTrans( ST_r,			letters+digits,	ST_ID			);
    setTrans( ST_re,		letters+digits,	ST_ID			);
    setTrans( ST_ret,		letters+digits,	ST_ID			);
    setTrans( ST_retu,		letters+digits,	ST_ID			);
    setTrans( ST_retur,		letters+digits,	ST_ID			);
    setTrans( ST_return,	letters+digits,	ST_ID			);
    setTrans( ST_N,			letters+digits,	ST_ID			);
    setTrans( ST_NU,		letters+digits,	ST_ID			);
    setTrans( ST_NUL,		letters+digits,	ST_ID			);
    setTrans( ST_NULL,		letters+digits,	ST_ID			);
    setTrans( ST_n,			letters+digits,	ST_ID			);
    setTrans( ST_ne,		letters+digits,	ST_ID			);
    setTrans( ST_new,		letters+digits,	ST_ID			);
    setTrans( ST_d,			letters+digits,	ST_ID			);
    setTrans( ST_de,		letters+digits,	ST_ID			);
    setTrans( ST_del,		letters+digits,	ST_ID			);
    setTrans( ST_dele,		letters+digits,	ST_ID			);
    setTrans( ST_delet,		letters+digits,	ST_ID			);
    setTrans( ST_delete,	letters+digits,	ST_ID			);
    setTrans( ST_START,		"(",			ST_LPAREN		);
    setTrans( ST_START,		")",			ST_RPAREN		);
    setTrans( ST_START,		"{",			ST_LBRACE		);
    setTrans( ST_START,		"}",			ST_RBRACE		);
    setTrans( ST_START,		"[",			ST_LBRACK		);
    setTrans( ST_START,		"]",			ST_RBRACK		);
    setTrans( ST_START,		"+",			ST_PLUS			);
    setTrans( ST_START,		"-",			ST_MINUS		);
    setTrans( ST_START,		"*",			ST_STAR			);
    setTrans( ST_START,		"/",			ST_SLASH		);
    setTrans( ST_START,		"%",			ST_PCT			);
    setTrans( ST_START,		",",			ST_COMMA		);
    setTrans( ST_START,		";",			ST_SEMI			);
    setTrans( ST_START,		"&",			ST_AMP			);
    setTrans( ST_SLASH,		"/",			ST_COMMENT		);
    setTrans( ST_START,		"<",			ST_LT			);
    setTrans( ST_START,		">",			ST_GT			);
    setTrans( ST_START,		"=",			ST_BECOMES		);
    setTrans( ST_START,		"!",			ST_NOT			);
    setTrans( ST_LT,		"=",			ST_LE			);
    setTrans( ST_GT,		"=",			ST_GE			);
    setTrans( ST_BECOMES,	"=",			ST_EQ			);
    setTrans( ST_NOT,		"=",			ST_NE			);
    setTrans( ST_START,		"w",			ST_w			);
    setTrans( ST_w,			"a",			ST_wa			);
    setTrans( ST_wa,		"i",			ST_wai			);
    setTrans( ST_wai,		"n",			ST_wain			);
    setTrans( ST_w,			"h",			ST_wh			);
    setTrans( ST_wh,		"i",			ST_whi			);
    setTrans( ST_whi,		"l",			ST_whil			);
    setTrans( ST_whil,		"e",			ST_while		);
    setTrans( ST_START,		"i",			ST_i			);
    setTrans( ST_i,			"n",			ST_in			);
    setTrans( ST_in,		"t",			ST_int			);
    setTrans( ST_i,			"f",			ST_if			);
    setTrans( ST_START,		"e",			ST_e			);
    setTrans( ST_e,			"l",			ST_el			);
    setTrans( ST_el,		"s",			ST_els			);
    setTrans( ST_els,		"e",			ST_else			);
    setTrans( ST_START,		"p",			ST_p			);
    setTrans( ST_p,			"r",			ST_pr			);
    setTrans( ST_pr,		"i",			ST_pri			);
    setTrans( ST_pri,		"n",			ST_prin			);
    setTrans( ST_prin,		"t",			ST_print		);
    setTrans( ST_print,		"l",			ST_printl		);
    setTrans( ST_printl,	"n",			ST_println		);
    setTrans( ST_START,		"r",			ST_r			);
    setTrans( ST_r,			"e",			ST_re			);
    setTrans( ST_re,		"t",			ST_ret			);
    setTrans( ST_ret,		"u",			ST_retu			);
    setTrans( ST_retu,		"r",			ST_retur		);
    setTrans( ST_retur,		"n",			ST_return		);
    setTrans( ST_START,		"N",			ST_N			);
    setTrans( ST_N,			"U",			ST_NU			);
    setTrans( ST_NU,		"L",			ST_NUL			);
    setTrans( ST_NUL,		"L",			ST_NULL			);
    setTrans( ST_START,		"n",			ST_n			);
    setTrans( ST_n,			"e",			ST_ne			);
    setTrans( ST_ne,		"w",			ST_new			);
    setTrans( ST_START,		"d",			ST_d			);
    setTrans( ST_d,			"e",			ST_de			);
    setTrans( ST_de,		"l",			ST_del			);
    setTrans( ST_del,		"e",			ST_dele			);
    setTrans( ST_dele,		"t",			ST_delet		);
    setTrans( ST_delet,		"e",			ST_delete		);
    
    setTrans( ST_START,		oneToNine,		ST_NUM			);
    setTrans( ST_NUM,		digits,			ST_NUM			);
    setTrans( ST_NUM,		letters,		ST_ERROR		);
    setTrans( ST_START,		"0",			ST_ZERO			);
    setTrans( ST_ZERO,		letters+digits,	ST_ERROR		);
    // A comment can only ever lead to the comment state
    for(int j=0; j < maxTrans; ++j) delta[ST_COMMENT][j] = ST_COMMENT;
}

// Set the transitions from one state to another state based upon characters in the
// given string
void ASM::Lexer::setTrans(ASM::State from, const string& chars, ASM::State to){
    for(string::const_iterator it = chars.begin(); it != chars.end(); ++it)
        delta[from][static_cast<unsigned int>(*it)] = to;
}

// Scan a line of input (as a string) and return a vector
// of Tokens representing the MIPS instruction in that line
vector<ASM::Token*> ASM::Lexer::scan(const string& line){
    // Return vector
    vector<Token*> ret;
    if(line.size() == 0) return ret;
    // Always begin at the start state
    State currState = ST_START;
    // startIter represents the beginning of the next Token
    // that is to be recognized. Initially, this is the beginning
    // of the line.
    // Use a const_iterator since we cannot change the input line
    string::const_iterator startIter = line.begin();
    // Loop over the the line
    for(string::const_iterator it = line.begin();;){
        // Assume the next state is the error state
        State nextState = ST_ERR;
        // If we aren't done then get the transition from the current
        // state to the next state based upon the current character of
        //input
        if(it != line.end())
            nextState = delta[currState][static_cast<unsigned int>(*it)];
        // If there is no valid transition then we have reach then end of a
        // Token and can add a new Token to the return vector
        if(ST_ERR == nextState){
            // Get the kind corresponding to the current state
            Kind currKind = stateKinds[currState];
            // If we are in an Error state then we have reached an invalid
            // Token - so we throw and error and delete the Tokens parsed
            // thus far
            if(ERR == currKind){
                vector<Token*>::iterator vit;
                for(vit = ret.begin(); vit != ret.end(); ++vit)
                    delete *vit;
                throw "ERROR in lexing after reading " + string(line.begin(),it);
            }
            if(NUM == currKind){
                if(string(startIter,it).length() > 10)
                {
                    vector<Token*>::iterator vit;
                    for(vit = ret.begin(); vit != ret.end(); ++vit)
                        delete *vit;
                    throw "ERROR: Numeric literal out of range" + string(line.begin(),it);
                }
                if(string(startIter,it).length() == 10 && string(startIter,it) > "2147483647")
                {
                    vector<Token*>::iterator vit;
                    for(vit = ret.begin(); vit != ret.end(); ++vit)
                        delete *vit;
                    throw "ERROR: Numeric literal out of range" + string(line.begin(),it);
                }
            }
            // If we are not in Whitespace then we push back a new token
            // based upon the kind of the State we end in
            // Whitespace is ignored for practical purposes
            if(WHITESPACE != currKind)
                ret.push_back(Token::makeToken(currKind,string(startIter,it)));
            // Start of next Token begins here
            startIter = it;
            // Revert to start state to begin recognizing next token
            currState = ST_START;
            if(it == line.end()) break;
        } else {
            // Otherwise we proceed to the next state and increment the iterator
            currState = nextState;
            ++it;
        }
    }
    return ret;
}



