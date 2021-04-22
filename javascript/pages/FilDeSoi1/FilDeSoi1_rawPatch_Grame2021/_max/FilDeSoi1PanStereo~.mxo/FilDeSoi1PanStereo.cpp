/* ------------------------------------------------------------
name: "FilDeSoi1PanStereo"
Code generated with Faust 2.30.7 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __FilDeSoi1PanStereo_H__
#define  __FilDeSoi1PanStereo_H__

/************************************************************************

    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2004-2020 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either version 3
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

    MAX MSP SDK : in order to compile a MaxMSP external with this
    architecture file you will need the official MaxMSP SDK from
    cycling'74. Please check the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

#ifdef WIN32
#ifndef NAN
    static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif
#endif

// FAUSTFLOAT is setup by faust2max6

#ifndef DOWN_SAMPLING
#define DOWN_SAMPLING 0
#endif
#ifndef UP_SAMPLING
#define UP_SAMPLING 0
#endif
#ifndef FILTER_TYPE
#define FILTER_TYPE 0
#endif

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN SimpleParser.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    int index;
    double init;
    double fmin;
    double fmax;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), fmin(0.), fmax(0.), step(0.)
    {}
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    std::cerr << "Parse error : " << errmsg << " here : " << p << std::endl;
    return true;
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
static bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] or [s]d[.dddd][E|e][s][dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    double sign = 1.0;     // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part
    double expsign = 1.0;  // sign of the E|e part
    double expcoef = 0.0;  // multiplication factor of E|e part
    
    bool valid = false;    // true if the number contains at least one digit
    
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    
    // Sign
    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    
    // Integral part
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    
    // Possible decimal part
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    
    // Possible E|e part
    if (parseChar(p, 'E') || parseChar(p, 'e')) {
        if (parseChar(p, '+')) {
            expsign = 1.0;
        } else if (parseChar(p, '-')) {
            expsign = -1.0;
        }
        while (isdigit(*p)) {
            expcoef = expcoef*10 + (*p - '0');
            p++;
        }
    }
    
    if (valid)  {
        x = (sign*(ipart + dpart/dcoef)) * std::pow(10.0, expcoef*expsign);
    } else {
        p = saved;
    }
    return valid;
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseString(const char*& p, char quote, std::string& s)
{
    std::string str;
    skipBlank(p);
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseSQString(const char*& p, std::string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseDQString(const char*& p, std::string& s)
{
    return parseString(p, '"', s);
}

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
static bool parseMenuItem(const char*& p, std::string& name, double& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

static bool parseMenuItem2(const char*& p, std::string& name)
{
    const char* saved = p;  // to restore position if we fail
    // single quoted
    if (parseSQString(p, name)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values)
{
    std::vector<std::string> tmpnames;
    std::vector<double> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            std::string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug)
{
    std::vector<std::string> tmpnames;
    const char* saved = p;  // to restore position if we fail
    
    if (parseChar(p, '{')) {
        do {
            std::string n;
            if (parseMenuItem2(p, n)) {
                tmpnames.push_back(n);
            } else {
                goto error;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            return true;
        }
    }
    
error:
    if (debug) { std::cerr << "parseMenuList2 : (" << saved << ") is not a valid list !\n"; }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of strings
/// ---------------------------------------------------------------------
static bool parseList(const char*& p, std::vector<std::string>& items)
{
    const char* saved = p;  // to restore position if we fail
    if (parseChar(p, '[')) {
        do {
            std::string item;
            if (!parseDQString(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    const char* saved = p; // to restore position if we fail
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
        }
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
    const char* saved = p; // to restore position if we fail
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        double dbl = 0;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo item;
                        item.type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].index = int(dbl);
                    }
                }
                
                else if (label == "meta") {
                    if (!parseItemMetaData(p, uiItems[numItems].meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].init = dbl;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmin = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmax = dbl;
                    }
                }
                
                else if (label == "step") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do {
                            if (!parseUI(p, uiItems, numItems)) {
                                p = saved;
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo item;
                            item.type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                p = saved;
                return false;
            }
            
        } while (tryChar(p, ','));
    
        return parseChar(p, '}');
    } else {
        return true; // "items": [] is valid
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p,
                      std::map<std::string, std::pair<std::string, double> >& metaDatas0,
                      std::map<std::string, std::string>& metaDatas1,
                      std::map<std::string, std::vector<std::string> >& metaDatas2,
                      std::vector<itemInfo>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        double dbl = 0;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, dbl, metaDatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metaDatas2[key] = items;
                    items.clear();
                } else if (value != "") {
                    metaDatas0[key].first = value;
                } else {
                    metaDatas0[key].second = dbl;
                }
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H
/**************************  END  SimpleParser.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        std::string buildLabel(std::string label)
        {
            std::replace(label.begin(), label.end(), ' ', '_');
            return label;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/
/************************** BEGIN dsp-combiner.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <string>
#include <assert.h>
#include <sstream>

/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  dsp.h **************************/

// Base class and common code for binary combiners

enum Layout { kVerticalGroup, kHorizontalGroup, kTabGroup };

class dsp_binary_combiner : public dsp {

    protected:

        dsp* fDSP1;
        dsp* fDSP2;
        int fBufferSize;
        Layout fLayout;
        std::string fLabel;

        void buildUserInterfaceAux(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }

        FAUSTFLOAT** allocateChannels(int num)
        {
            FAUSTFLOAT** channels = new FAUSTFLOAT*[num];
            for (int chan = 0; chan < num; chan++) {
                channels[chan] = new FAUSTFLOAT[fBufferSize];
                memset(channels[chan], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            return channels;
        }

        void deleteChannels(FAUSTFLOAT** channels, int num)
        {
            for (int chan = 0; chan < num; chan++) {
                delete [] channels[chan];
            }
            delete [] channels;
        }

     public:

        dsp_binary_combiner(dsp* dsp1, dsp* dsp2, int buffer_size, Layout layout, const std::string& label)
        :fDSP1(dsp1), fDSP2(dsp2), fBufferSize(buffer_size), fLayout(layout), fLabel(label)
        {}

        virtual ~dsp_binary_combiner()
        {
            delete fDSP1;
            delete fDSP2;
        }

        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
        virtual void init(int sample_rate)
        {
            fDSP1->init(sample_rate);
            fDSP2->init(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            fDSP1->instanceInit(sample_rate);
            fDSP2->instanceInit(sample_rate);
        }
        virtual void instanceConstants(int sample_rate)
        {
            fDSP1->instanceConstants(sample_rate);
            fDSP2->instanceConstants(sample_rate);
        }

        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }

        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }

        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }

};

// Combine two 'compatible' DSP in sequence

class dsp_sequencer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;

    public:

        dsp_sequencer(dsp* dsp1, dsp* dsp2,
                      int buffer_size = 4096,
                      Layout layout = Layout::kTabGroup,
                      const std::string& label = "Sequencer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
        }

        virtual ~dsp_sequencer()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);
            fDSP2->compute(count, fDSP1Outputs, outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_parallelizer(dsp* dsp1, dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Parallelizer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fDSP2Outputs = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
        }

        virtual ~dsp_parallelizer()
        {
            delete [] fDSP2Inputs;
            delete [] fDSP2Outputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);

            // Shift inputs/outputs channels for fDSP2
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                fDSP2Inputs[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                fDSP2Outputs[chan] = outputs[fDSP1->getNumOutputs() + chan];
            }

            fDSP2->compute(count, fDSP2Inputs, fDSP2Outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two 'compatible' DSP in splitter

class dsp_splitter : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

    public:

        dsp_splitter(dsp* dsp1, dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Splitter")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_splitter()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_splitter(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);

            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                 fDSP2Inputs[chan] = fDSP1Outputs[chan % fDSP1->getNumOutputs()];
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in merger

class dsp_merger : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

        void mix(int count, FAUSTFLOAT* dst, FAUSTFLOAT* src)
        {
            for (int frame = 0; frame < count; frame++) {
                dst[frame] += src[frame];
            }
        }

    public:

        dsp_merger(dsp* dsp1, dsp* dsp2,
                   int buffer_size = 4096,
                   Layout layout = Layout::kTabGroup,
                   const std::string& label = "Merger")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_merger()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_merger(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, fDSP1Inputs, fDSP1Outputs);

            memset(fDSP2Inputs, 0, sizeof(FAUSTFLOAT*) * fDSP2->getNumInputs());

            for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                int mchan = chan % fDSP2->getNumInputs();
                if (fDSP2Inputs[mchan]) {
                    mix(count, fDSP2Inputs[mchan], fDSP1Outputs[chan]);
                } else {
                    fDSP2Inputs[mchan] = fDSP1Outputs[chan];
                }
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in a recursive way

class dsp_recursiver : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_recursiver(dsp* dsp1, dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Recursiver")
        :dsp_binary_combiner(dsp1, dsp2, 1, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = allocateChannels(fDSP2->getNumInputs());
            fDSP2Outputs = allocateChannels(fDSP2->getNumOutputs());
        }

        virtual ~dsp_recursiver()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            deleteChannels(fDSP2Inputs, fDSP2->getNumInputs());
            deleteChannels(fDSP2Outputs, fDSP2->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() - fDSP2->getNumOutputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_recursiver(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int frame = 0; (frame < count); frame++) {

                for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan][0] = fDSP2Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP1->getNumInputs() - fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan + fDSP2->getNumOutputs()][0] = inputs[chan][frame];
                }

                fDSP1->compute(1, fDSP1Inputs, fDSP1Outputs);

                for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                    outputs[chan][frame] = fDSP1Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                    fDSP2Inputs[chan][0] = fDSP1Outputs[chan][0];
                }

                fDSP2->compute(1, fDSP2Inputs, fDSP2Outputs);
            }
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

#ifndef __dsp_algebra_api__
#define __dsp_algebra_api__

// DSP algebra API
/*
 Each operation takes two DSP and a optional Layout and Label parameters, returns the combined DSPs, or null if failure with an error message.
 */

static dsp* createDSPSequencer(dsp* dsp1, dsp* dsp2,
                               std::string& error,
                               Layout layout = Layout::kTabGroup,
                               const std::string& label = "Sequencer")
{
    if (dsp1->getNumOutputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error int dsp_sequencer : the number of outputs ("
                  << dsp1->getNumOutputs() << ") of A "
                  << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    }
}

static dsp* createDSPParallelizer(dsp* dsp1, dsp* dsp2,
                                  std::string& error,
                                  Layout layout = Layout::kTabGroup,
                                  const std::string& label = "Parallelizer")
{
    return new dsp_parallelizer(dsp1, dsp2, 4096, layout, label);
}

static dsp* createDSPSplitter(dsp* dsp1, dsp* dsp2, std::string& error, Layout layout = Layout::kTabGroup, const std::string& label = "Splitter")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_splitter : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_splitter : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() % dsp1->getNumOutputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_splitter : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a divisor of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_splitter(dsp1, dsp2, 4096, layout, label);
    }
}

static dsp* createDSPMerger(dsp* dsp1, dsp* dsp2,
                            std::string& error,
                            Layout layout = Layout::kTabGroup,
                            const std::string& label = "Merger")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_merger : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_merger : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp1->getNumOutputs() % dsp2->getNumInputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_merger : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a multiple of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_merger(dsp1, dsp2, 4096, layout, label);
    }
}

static dsp* createDSPRecursiver(dsp* dsp1, dsp* dsp2,
                                std::string& error,
                                Layout layout = Layout::kTabGroup,
                                const std::string& label = "Recursiver")
{
    if ((dsp2->getNumInputs() > dsp1->getNumOutputs()) || (dsp2->getNumOutputs() > dsp1->getNumInputs())) {
        std::stringstream error_aux;
        error_aux << "Connection error in : dsp_recursiver" << std::endl;
        if (dsp2->getNumInputs() > dsp1->getNumOutputs()) {
            error_aux << "The number of outputs " << dsp1->getNumOutputs()
                      << " of the first expression should be greater or equal to the number of inputs ("
                      << dsp2->getNumInputs()
                      << ") of the second expression" << std::endl;
        }
        if (dsp2->getNumOutputs() > dsp1->getNumInputs()) {
            error_aux << "The number of inputs " << dsp1->getNumInputs()
                      << " of the first expression should be greater or equal to the number of outputs ("
                      << dsp2->getNumOutputs()
                      << ") of the second expression" << std::endl;
        }
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_recursiver(dsp1, dsp2, layout, label);
    }
}
#endif

#endif
/**************************  END  dsp-combiner.h **************************/
/************************** BEGIN dsp-adapter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_adapter__
#define __dsp_adapter__

#ifndef _WIN32
#include <alloca.h>
#endif
#include <string.h>
#include <iostream>
#include <cmath>
#include <assert.h>


// Adapts a DSP for a different number of inputs/outputs
class dsp_adapter : public decorator_dsp {
    
    private:
    
        FAUSTFLOAT** fAdaptedInputs;
        FAUSTFLOAT** fAdaptedOutputs;
        int fHWInputs;
        int fHWOutputs;
        int fBufferSize;
    
        void adaptBuffers(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fHWInputs; i++) {
                fAdaptedInputs[i] = inputs[i];
            }
            for (int i = 0; i < fHWOutputs; i++) {
                fAdaptedOutputs[i] = outputs[i];
            }
        }
    
    public:
    
        dsp_adapter(dsp* dsp, int hw_inputs, int hw_outputs, int buffer_size):decorator_dsp(dsp)
        {
            fHWInputs = hw_inputs;
            fHWOutputs = hw_outputs;
            fBufferSize = buffer_size;
            
            fAdaptedInputs = new FAUSTFLOAT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs() - fHWInputs; i++) {
                fAdaptedInputs[i + fHWInputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedInputs[i + fHWInputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            
            fAdaptedOutputs = new FAUSTFLOAT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs() - fHWOutputs; i++) {
                fAdaptedOutputs[i + fHWOutputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedOutputs[i + fHWOutputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
    
        virtual ~dsp_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs() - fHWInputs; i++) {
                delete [] fAdaptedInputs[i + fHWInputs];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs() - fHWOutputs; i++) {
                delete [] fAdaptedOutputs[i + fHWOutputs];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual int getNumInputs() { return fHWInputs; }
        virtual int getNumOutputs() { return fHWOutputs; }
    
        virtual dsp_adapter* clone() { return new dsp_adapter(fDSP->clone(), fHWInputs, fHWOutputs, fBufferSize); }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(date_usec, count, fAdaptedInputs, fAdaptedOutputs);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(count, fAdaptedInputs, fAdaptedOutputs);
        }
};

// Adapts a DSP for a different sample size
template <typename REAL_INT, typename REAL_EXT>
class dsp_sample_adapter : public decorator_dsp {
    
    private:
    
        REAL_INT** fAdaptedInputs;
        REAL_INT** fAdaptedOutputs;
    
        void adaptInputBuffers(int count, FAUSTFLOAT** inputs)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    fAdaptedInputs[chan][frame] = REAL_INT(reinterpret_cast<REAL_EXT**>(inputs)[chan][frame]);
                }
            }
        }
    
        void adaptOutputsBuffers(int count, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    reinterpret_cast<REAL_EXT**>(outputs)[chan][frame] = REAL_EXT(fAdaptedOutputs[chan][frame]);
                }
            }
        }
    
    public:
    
        dsp_sample_adapter(dsp* dsp):decorator_dsp(dsp)
        {
            fAdaptedInputs = new REAL_INT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs(); i++) {
                fAdaptedInputs[i] = new REAL_INT[4096];
            }
            
            fAdaptedOutputs = new REAL_INT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs(); i++) {
                fAdaptedOutputs[i] = new REAL_INT[4096];
            }
        }
    
        virtual ~dsp_sample_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fAdaptedInputs[i];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fAdaptedOutputs[i];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual dsp_sample_adapter* clone() { return new dsp_sample_adapter(fDSP->clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
};

// Template used to specialize double parameters expressed as NUM/DENOM
template <int NUM, int DENOM>
struct Double {
    static constexpr double value() { return double(NUM)/double(DENOM); }
};

// Base class for filters
template <class fVslider0, int fVslider1>
struct Filter {
    inline int getFactor() { return fVslider1; }
};

// Identity filter: copy input to output
template <class fVslider0, int fVslider1>
struct Identity : public Filter<fVslider0, fVslider1> {
    inline int getFactor() { return fVslider1; }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        memcpy(output0, input0, count * sizeof(FAUSTFLOAT));
    }
};

// Generated with process = fi.lowpass(3, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3 : public Filter<fVslider0, fVslider1> {
    
    REAL fVec0[2];
    REAL fRec1[2];
    REAL fRec0[3];
    
    inline REAL LowPass3_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3()
    {
        for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
            fVec0[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 1.0000000000000002) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (fSlow1 + 1.0));
        REAL fSlow4 = (1.0 - fSlow1);
        REAL fSlow5 = (((fSlow1 + -1.0000000000000002) / fSlow0) + 1.0);
        REAL fSlow6 = (2.0 * (1.0 - (1.0 / LowPass3_faustpower2_f(fSlow0))));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            REAL fTemp0 = REAL(input0[i]);
            fVec0[0] = fTemp0;
            fRec1[0] = (0.0 - (fSlow3 * ((fSlow4 * fRec1[1]) - (fTemp0 + fVec0[1]))));
            fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow5 * fRec0[2]) + (fSlow6 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fVec0[1] = fVec0[0];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass(4, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass4 : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass4_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass4()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0f;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec0[l1] = 0.0f;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.76536686473017945) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (((fSlow1 + 1.8477590650225735) / fSlow0) + 1.0));
        REAL fSlow4 = (((fSlow1 + -1.8477590650225735) / fSlow0) + 1.0);
        REAL fSlow5 = (2.0 * (1.0 - (1.0 / LowPass4_faustpower2_f(fSlow0))));
        REAL fSlow6 = (((fSlow1 + -0.76536686473017945) / fSlow0) + 1.0);
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow3 * ((fSlow4 * fRec1[2]) + (fSlow5 * fRec1[1]))));
            fRec0[0] = ((fSlow3 * (fRec1[2] + (fRec1[0] + (2.0 * fRec1[1])))) - (fSlow2 * ((fSlow6 * fRec0[2]) + (fSlow5 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass3e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fVec0[2];
    REAL fRec0[2];
    
    inline REAL LowPass3e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fVec0[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (fSlow1 + 0.82244590899881598));
        REAL fSlow3 = (0.82244590899881598 - fSlow1);
        REAL fSlow4 = (1.0 / (((fSlow1 + 0.80263676416103003) / fSlow0) + 1.4122708937742039));
        REAL fSlow5 = LowPass3e_faustpower2_f(fSlow0);
        REAL fSlow6 = (0.019809144837788999 / fSlow5);
        REAL fSlow7 = (fSlow6 + 1.1615164189826961);
        REAL fSlow8 = (((fSlow1 + -0.80263676416103003) / fSlow0) + 1.4122708937742039);
        REAL fSlow9 = (2.0 * (1.4122708937742039 - (1.0 / fSlow5)));
        REAL fSlow10 = (2.0 * (1.1615164189826961 - fSlow6));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow4 * ((fSlow8 * fRec1[2]) + (fSlow9 * fRec1[1]))));
            REAL fTemp0 = (fSlow4 * (((fSlow7 * fRec1[0]) + (fSlow10 * fRec1[1])) + (fSlow7 * fRec1[2])));
            fVec0[0] = fTemp0;
            fRec0[0] = (0.0 - (fSlow2 * ((fSlow3 * fRec0[1]) - (fTemp0 + fVec0[1]))));
            output0[i] = FAUSTFLOAT(fRec0[0]);
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fVec0[1] = fVec0[0];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass6e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass6e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec2[3];
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass6e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass6e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec2[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.16840487111358901) / fSlow0) + 1.0693584077073119));
        REAL fSlow3 = LowPass6e_faustpower2_f(fSlow0);
        REAL fSlow4 = (1.0 / fSlow3);
        REAL fSlow5 = (fSlow4 + 53.536152954556727);
        REAL fSlow6 = (1.0 / (((fSlow1 + 0.51247864188914105) / fSlow0) + 0.68962136448467504));
        REAL fSlow7 = (fSlow4 + 7.6217312988706034);
        REAL fSlow8 = (1.0 / (((fSlow1 + 0.78241304682164503) / fSlow0) + 0.24529150870616001));
        REAL fSlow9 = (9.9999997054999994e-05 / fSlow3);
        REAL fSlow10 = (fSlow9 + 0.00043322720055500002);
        REAL fSlow11 = (((fSlow1 + -0.78241304682164503) / fSlow0) + 0.24529150870616001);
        REAL fSlow12 = (2.0 * (0.24529150870616001 - fSlow4));
        REAL fSlow13 = (2.0 * (0.00043322720055500002 - fSlow9));
        REAL fSlow14 = (((fSlow1 + -0.51247864188914105) / fSlow0) + 0.68962136448467504);
        REAL fSlow15 = (2.0 * (0.68962136448467504 - fSlow4));
        REAL fSlow16 = (2.0 * (7.6217312988706034 - fSlow4));
        REAL fSlow17 = (((fSlow1 + -0.16840487111358901) / fSlow0) + 1.0693584077073119);
        REAL fSlow18 = (2.0 * (1.0693584077073119 - fSlow4));
        REAL fSlow19 = (2.0 * (53.536152954556727 - fSlow4));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec2[0] = (REAL(input0[i]) - (fSlow8 * ((fSlow11 * fRec2[2]) + (fSlow12 * fRec2[1]))));
            fRec1[0] = ((fSlow8 * (((fSlow10 * fRec2[0]) + (fSlow13 * fRec2[1])) + (fSlow10 * fRec2[2]))) - (fSlow6 * ((fSlow14 * fRec1[2]) + (fSlow15 * fRec1[1]))));
            fRec0[0] = ((fSlow6 * (((fSlow7 * fRec1[0]) + (fSlow16 * fRec1[1])) + (fSlow7 * fRec1[2]))) - (fSlow2 * ((fSlow17 * fRec0[2]) + (fSlow18 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (((fSlow5 * fRec0[0]) + (fSlow19 * fRec0[1])) + (fSlow5 * fRec0[2]))));
            fRec2[2] = fRec2[1];
            fRec2[1] = fRec2[0];
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// A "si.bus(N)" like hard-coded class
struct dsp_bus : public dsp {
    
    int fChannels;
    int fSampleRate;
    
    dsp_bus(int channels):fChannels(channels), fSampleRate(-1)
    {}
    
    virtual int getNumInputs() { return fChannels; }
    virtual int getNumOutputs() { return fChannels; }
    
    virtual int getSampleRate() { return fSampleRate; }
    
    virtual void buildUserInterface(UI* ui_interface) {}
    virtual void init(int sample_rate)
    {
        //classInit(sample_rate);
        instanceInit(sample_rate);
    }
    
    virtual void instanceInit(int sample_rate)
    {
        fSampleRate = sample_rate;
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }
    
    virtual void instanceConstants(int sample_rate) {}
    virtual void instanceResetUserInterface() {}
    virtual void instanceClear() {}
    
    virtual dsp* clone() { return new dsp_bus(fChannels); }
    
    virtual void metadata(Meta* m) {}
    
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        for (int chan = 0; chan < fChannels; chan++) {
            memcpy(outputs[chan], inputs[chan], sizeof(FAUSTFLOAT) * count);
        }
    }
    
    virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

// Base class for sample-rate adapter
template <typename FILTER>
class sr_sampler : public decorator_dsp {
    
    protected:
    
        std::vector<FILTER> fInputLowPass;
        std::vector<FILTER> fOutputLowPass;
    
        inline int getFactor() { return this->fOutputLowPass[0].getFactor(); }
    
    public:
    
        sr_sampler(dsp* dsp):decorator_dsp(dsp)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                fInputLowPass.push_back(FILTER());
            }
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                fOutputLowPass.push_back(FILTER());
            }
        }
};

// Down sample-rate adapter
template <typename FILTER>
class dsp_down_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_down_sampler(dsp* dsp):sr_sampler<FILTER>(dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate / this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate / this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate / this->getFactor());
        }
    
        virtual dsp_down_sampler* clone() { return new dsp_down_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count / this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Lowpass filtering in place on 'inputs'
                this->fInputLowPass[chan].compute(count, inputs[chan], inputs[chan]);
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Decimate
                for (int frame = 0; frame < real_count; frame++) {
                    fInputs[chan][frame] = inputs[chan][frame * this->getFactor()];
                }
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at lower rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Puts zeros
                memset(outputs[chan], 0, sizeof(FAUSTFLOAT) * count);
                for (int frame = 0; frame < real_count; frame++) {
                    // Copy one sample every 'DownFactor'
                    // Apply volume
                    //outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame] * this->getFactor();
                    outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame];
                }
                // Lowpass filtering in place on 'outputs'
                this->fOutputLowPass[chan].compute(count, outputs[chan], outputs[chan]);
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Up sample-rate adapter
template <typename FILTER>
class dsp_up_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_up_sampler(dsp* dsp):sr_sampler<FILTER>(dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate * this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate * this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate * this->getFactor());
        }
    
        virtual dsp_up_sampler* clone() { return new dsp_up_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count * this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Puts zeros
                memset(fInputs[chan], 0, sizeof(FAUSTFLOAT) * real_count);
                for (int frame = 0; frame < count; frame++) {
                    // Copy one sample every 'UpFactor'
                    fInputs[chan][frame * this->getFactor()] = inputs[chan][frame];
                }
                // Lowpass filtering in place on 'fInputs'
                this->fInputLowPass[chan].compute(real_count, fInputs[chan], fInputs[chan]);
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at upper rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Lowpass filtering in place on 'fOutputs'
                this->fOutputLowPass[chan].compute(real_count, fOutputs[chan], fOutputs[chan]);
                // Decimate
                for (int frame = 0; frame < count; frame++) {
                    // Apply volume
                    //outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()] * this->getFactor();
                    outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()];
                }
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Create a UP/DS + Filter adapted DSP
template <typename REAL>
dsp* createSRAdapter(dsp* DSP, int ds = 0, int us = 0, int filter = 0)
{
    if (ds > 0) {
        switch (filter) {
            case 0:
                if (ds == 2) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    std::cerr << "ERROR : ds factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : ds factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : ds factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : ds factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : ds factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            default:
                std::cerr << "ERROR : filter type must be in [0..4] range\n";
                assert(false);
                return nullptr;
        }
    } else if (us > 0) {
        
        switch (filter) {
            case 0:
                if (us == 2) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    std::cerr << "ERROR : us factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : us factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : us factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : us factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    std::cerr << "ERROR : us factor type must be in [2..32] range\n";
                    assert(false);
                    return nullptr;
                }
            default:
                std::cerr << "ERROR : filter type must be in [0..4] range\n";
                assert(false);
                return nullptr;
        }
    } else {
        return DSP;
    }
}
    
#endif
/**************************  END  dsp-adapter.h **************************/
/************************** BEGIN misc.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <string>

/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

static int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

static int int2pow2(int x) { int r = 0; while ((1<<r) < x) r++; return r; }

static long lopt(char* argv[], const char* name, long def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return std::atoi(argv[i+1]);
    return def;
}

static long lopt1(int argc, char* argv[], const char* longname, const char* shortname, long def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return atoi(argv[i]);
        }
    }
    return def;
}

static const char* lopts(char* argv[], const char* name, const char* def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
    return def;
}

static const char* lopts1(int argc, char* argv[], const char* longname, const char* shortname, const char* def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return argv[i];
        }
    }
    return def;
}

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

static std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    std::string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

#endif

/**************************  END  misc.h **************************/
/************************** BEGIN SaveUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_SAVEUI_H
#define FAUST_SAVEUI_H

/************************** BEGIN DecoratorUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef Decorator_UI_H
#define Decorator_UI_H


//----------------------------------------------------------------
//  Generic UI empty implementation
//----------------------------------------------------------------

class GenericUI : public UI
{
    
    public:
        
        GenericUI() {}
        virtual ~GenericUI() {}
        
        // -- widget's layouts
        virtual void openTabBox(const char* label) {}
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* soundpath, Soundfile** sf_zone) {}
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
    
};

//----------------------------------------------------------------
//  Generic UI decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    
    protected:
        
        UI* fUI;
        
    public:
        
        DecoratorUI(UI* ui = 0):fUI(ui) {}
        virtual ~DecoratorUI() { delete fUI; }
        
        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addNumEntry(label, zone, init, min, max, step); }
        
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addVerticalBargraph(label, zone, min, max); }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) { fUI->addSoundfile(label, filename, sf_zone); }
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }
    
};

#endif
/**************************  END  DecoratorUI.h **************************/

// Base class to handle controllers state save/load

class SaveUI : public GenericUI {

    protected:
    
        struct SavedZone {
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fCurrent;
            FAUSTFLOAT fInit;
            
            SavedZone():fZone(nullptr), fCurrent(FAUSTFLOAT(0)), fInit(FAUSTFLOAT(0))
            {}
            SavedZone(FAUSTFLOAT* zone, FAUSTFLOAT current, FAUSTFLOAT init)
            :fZone(zone), fCurrent(current), fInit(init)
            {
                *fZone = current;
            }
            ~SavedZone()
            {}
        };
        
        std::map<std::string, SavedZone> fName2Zone;
    
        virtual void addItem(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init) = 0;
    
    public:
    
        SaveUI() {}
        virtual ~SaveUI() {}
    
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addItem(label, zone, FAUSTFLOAT(0));
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addItem(label, zone, FAUSTFLOAT(0));
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addItem(label, zone, init);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addItem(label, zone, init);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addItem(label, zone, init);
        }

        void reset()
        {
            for (auto& it : fName2Zone) {
                *it.second.fZone = it.second.fInit;
            }
        }
        
        void display()
        {
            for (auto& it : fName2Zone) {
                std::cout << "SaveUI::display path = " << it.first << " value = " << *it.second.fZone << std::endl;
            }
        }
        
        void save()
        {
            for (auto& it : fName2Zone) {
                it.second.fCurrent = *it.second.fZone;
            }
        }
};

/*
 Save/load current value using the label, reset to init value
 */

class SaveLabelUI : public SaveUI {
    
    protected:
    
        void addItem(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init)
        {
            if (fName2Zone.find(label) != fName2Zone.end()) {
                FAUSTFLOAT current = fName2Zone[label].fCurrent;
                fName2Zone[label] = SavedZone(zone, current, init);
            } else {
                fName2Zone[label] = SavedZone(zone, init, init);
            }
        }
        
    public:
        
        SaveLabelUI() : SaveUI() {}
        virtual ~SaveLabelUI() {}        
   
};

/*
 Save/load current value using the complete path, reset to init value
*/

class SavePathUI : public SaveUI, public PathBuilder {
    
    protected:
    
        void openTabBox(const char* label) { pushLabel(label); }
        void openHorizontalBox(const char* label) { pushLabel(label);; }
        void openVerticalBox(const char* label) { pushLabel(label); }
        void closeBox() { popLabel(); };
    
        void addItem(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init)
        {
            std::string path = buildPath(label);
            if (fName2Zone.find(path) != fName2Zone.end()) {
                FAUSTFLOAT current = fName2Zone[path].fCurrent;
                fName2Zone[path] = SavedZone(zone, current, init);
            } else {
                fName2Zone[path] = SavedZone(zone, init, init);
            }
        }
   
    public:

        SavePathUI(): SaveUI() {}
        virtual ~SavePathUI() {}

};

#endif

/**************************  END  SaveUI.h **************************/

// Always included
/************************** BEGIN OSCUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __OSCUI__
#define __OSCUI__

#include <vector>
#include <string>

/*

  Faust Project

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __OSCControler__
#define __OSCControler__

#include <string>
/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __FaustFactory__
#define __FaustFactory__

#include <stack>
#include <string>
#include <sstream>

/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __FaustNode__
#define __FaustNode__

#include <string>
#include <vector>

/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __MessageDriven__
#define __MessageDriven__

#include <string>
#include <vector>

/*

  Copyright (C) 2010  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __MessageProcessor__
#define __MessageProcessor__

namespace oscfaust
{

class Message;
//--------------------------------------------------------------------------
/*!
	\brief an abstract class for objects able to process OSC messages	
*/
class MessageProcessor
{
	public:
		virtual		~MessageProcessor() {}
		virtual void processMessage( const Message* msg ) = 0;
};

} // end namespoace

#endif
/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __smartpointer__
#define __smartpointer__

#include <cassert>

namespace oscfaust
{

/*!
\brief the base class for smart pointers implementation

	Any object that want to support smart pointers should
	inherit from the smartable class which provides reference counting
	and automatic delete when the reference count drops to zero.
*/
class smartable {
	private:
		unsigned 	refCount;		
	public:
		//! gives the reference count of the object
		unsigned refs() const         { return refCount; }
		//! addReference increments the ref count and checks for refCount overflow
		void addReference()           { refCount++; assert(refCount != 0); }
		//! removeReference delete the object when refCount is zero		
		void removeReference()		  { if (--refCount == 0) delete this; }
		
	protected:
		smartable() : refCount(0) {}
		smartable(const smartable&): refCount(0) {}
		//! destructor checks for non-zero refCount
		virtual ~smartable()    
        { 
            /* 
                See "Static SFaustNode create (const char* name, C* zone, C init, C min, C max, const char* prefix, GUI* ui)" comment.
                assert (refCount == 0); 
            */
        }
		smartable& operator=(const smartable&) { return *this; }
};

/*!
\brief the smart pointer implementation

	A smart pointer is in charge of maintaining the objects reference count 
	by the way of pointers operators overloading. It supports class 
	inheritance and conversion whenever possible.
\n	Instances of the SMARTP class are supposed to use \e smartable types (or at least
	objects that implements the \e addReference and \e removeReference
	methods in a consistent way).
*/
template<class T> class SMARTP {
	private:
		//! the actual pointer to the class
		T* fSmartPtr;

	public:
		//! an empty constructor - points to null
		SMARTP()	: fSmartPtr(0) {}
		//! build a smart pointer from a class pointer
		SMARTP(T* rawptr) : fSmartPtr(rawptr)              { if (fSmartPtr) fSmartPtr->addReference(); }
		//! build a smart pointer from an convertible class reference
		template<class T2> 
		SMARTP(const SMARTP<T2>& ptr) : fSmartPtr((T*)ptr) { if (fSmartPtr) fSmartPtr->addReference(); }
		//! build a smart pointer from another smart pointer reference
		SMARTP(const SMARTP& ptr) : fSmartPtr((T*)ptr)     { if (fSmartPtr) fSmartPtr->addReference(); }

		//! the smart pointer destructor: simply removes one reference count
		~SMARTP()  { if (fSmartPtr) fSmartPtr->removeReference(); }
		
		//! cast operator to retrieve the actual class pointer
		operator T*() const  { return fSmartPtr;	}

		//! '*' operator to access the actual class pointer
		T& operator*() const {
			// checks for null dereference
			assert (fSmartPtr != 0);
			return *fSmartPtr;
		}

		//! operator -> overloading to access the actual class pointer
		T* operator->() const	{ 
			// checks for null dereference
			assert (fSmartPtr != 0);
			return fSmartPtr;
		}

		//! operator = that moves the actual class pointer
		template <class T2>
		SMARTP& operator=(T2 p1_)	{ *this=(T*)p1_; return *this; }

		//! operator = that moves the actual class pointer
		SMARTP& operator=(T* p_)	{
			// check first that pointers differ
			if (fSmartPtr != p_) {
				// increments the ref count of the new pointer if not null
				if (p_ != 0) p_->addReference();
				// decrements the ref count of the old pointer if not null
				if (fSmartPtr != 0) fSmartPtr->removeReference();
				// and finally stores the new actual pointer
				fSmartPtr = p_;
			}
			return *this;
		}
		//! operator < to support SMARTP map with Visual C++
		bool operator<(const SMARTP<T>& p_)	const			  { return fSmartPtr < ((T *) p_); }
		//! operator = to support inherited class reference
		SMARTP& operator=(const SMARTP<T>& p_)                { return operator=((T *) p_); }
		//! dynamic cast support
		template<class T2> SMARTP& cast(T2* p_)               { return operator=(dynamic_cast<T*>(p_)); }
		//! dynamic cast support
		template<class T2> SMARTP& cast(const SMARTP<T2>& p_) { return operator=(dynamic_cast<T*>(p_)); }
};

}

#endif

namespace oscfaust
{

class Message;
class OSCRegexp;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
/*!
	\brief a base class for objects accepting OSC messages
	
	Message driven objects are hierarchically organized in a tree.
	They provides the necessary to dispatch an OSC message to its destination
	node, according to the message OSC address. 
	
	The principle of the dispatch is the following:
	- first the processMessage() method should be called on the top level node
	- next processMessage call propose 
*/
class MessageDriven : public MessageProcessor, public smartable
{
	std::string						fName;			///< the node name
	std::string						fOSCPrefix;		///< the node OSC address prefix (OSCAddress = fOSCPrefix + '/' + fName)
	std::vector<SMessageDriven>		fSubNodes;		///< the subnodes of the current node

	protected:
				 MessageDriven(const char *name, const char *oscprefix) : fName (name), fOSCPrefix(oscprefix) {}
		virtual ~MessageDriven() {}

	public:
		static SMessageDriven create(const char* name, const char *oscprefix)	{ return new MessageDriven(name, oscprefix); }

		/*!
			\brief OSC message processing method.
			\param msg the osc message to be processed
			The method should be called on the top level node.
		*/
		virtual void	processMessage(const Message* msg);

		/*!
			\brief propose an OSc message at a given hierarchy level.
			\param msg the osc message currently processed
			\param regexp a regular expression based on the osc address head
			\param addrTail the osc address tail
			
			The method first tries to match the regular expression with the object name. 
			When it matches:
			- it calls \c accept when \c addrTail is empty 
			- or it \c propose the message to its subnodes when \c addrTail is not empty. 
			  In this case a new \c regexp is computed with the head of \c addrTail and a new \c addrTail as well.
		*/
		virtual void	propose(const Message* msg, const OSCRegexp* regexp, const std::string& addrTail);

		/*!
			\brief accept an OSC message. 
			\param msg the osc message currently processed
			\return true when the message is processed by the node
			
			The method is called only for the destination nodes. The real message acceptance is the node 
			responsability and may depend on the message content.
		*/
		virtual bool	accept(const Message* msg);

		/*!
			\brief handler for the \c 'get' message
			\param ipdest the output message destination IP
			
			The \c 'get' message is supported by every node:
			- it is propagated to the subnodes until it reaches terminal nodes
			- a terminal node send its state on \c 'get' request to the IP address given as parameter.
			The \c get method is basically called by the accept method.
		*/
		virtual void	get(unsigned long ipdest) const;

		/*!
			\brief handler for the \c 'get' 'attribute' message
			\param ipdest the output message destination IP
			\param what the requested attribute
			
			The \c 'get' message is supported by every node:
			- it is propagated to the subnodes until it reaches terminal nodes
			- a terminal node send its state on \c 'get' request to the IP address given as parameter.
			The \c get method is basically called by the accept method.
		*/
		virtual void	get(unsigned long ipdest, const std::string& what) const {}

		void			add(SMessageDriven node)	{ fSubNodes.push_back (node); }
		const char*		getName() const				{ return fName.c_str(); }
		std::string		getOSCAddress() const;
		int				size() const				{ return (int)fSubNodes.size (); }
		
		const std::string&	name() const			{ return fName; }
		SMessageDriven	subnode(int i)              { return fSubNodes[i]; }
};

} // end namespoace

#endif
/*

  Copyright (C) 2011  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __Message__
#define __Message__

#include <string>
#include <vector>

namespace oscfaust
{

class OSCStream;
template <typename T> class MsgParam;
class baseparam;
typedef SMARTP<baseparam>	Sbaseparam;

//--------------------------------------------------------------------------
/*!
	\brief base class of a message parameters
*/
class baseparam : public smartable
{
	public:
		virtual ~baseparam() {}

		/*!
		 \brief utility for parameter type checking
		*/
		template<typename X> bool isType() const { return dynamic_cast<const MsgParam<X>*> (this) != 0; }
		/*!
		 \brief utility for parameter convertion
		 \param errvalue the returned value when no conversion applies
		 \return the parameter value when the type matches
		*/
		template<typename X> X	value(X errvalue) const 
			{ const MsgParam<X>* o = dynamic_cast<const MsgParam<X>*> (this); return o ? o->getValue() : errvalue; }
		/*!
		 \brief utility for parameter comparison
		*/
		template<typename X> bool	equal(const baseparam& p) const 
			{ 
				const MsgParam<X>* a = dynamic_cast<const MsgParam<X>*> (this); 
				const MsgParam<X>* b = dynamic_cast<const MsgParam<X>*> (&p);
				return a && b && (a->getValue() == b->getValue());
			}
		/*!
		 \brief utility for parameter comparison
		*/
		bool operator==(const baseparam& p) const 
			{ 
				return equal<float>(p) || equal<int>(p) || equal<std::string>(p);
			}
		bool operator!=(const baseparam& p) const
			{ 
				return !equal<float>(p) && !equal<int>(p) && !equal<std::string>(p);
			}
			
		virtual SMARTP<baseparam> copy() const = 0;
};

//--------------------------------------------------------------------------
/*!
	\brief template for a message parameter
*/
template <typename T> class MsgParam : public baseparam
{
	T fParam;
	public:
				 MsgParam(T val) : fParam(val)	{}
		virtual ~MsgParam() {}
		
		T getValue() const { return fParam; }
		
		virtual Sbaseparam copy() const { return new MsgParam<T>(fParam); }
};

//--------------------------------------------------------------------------
/*!
	\brief a message description
	
	A message is composed of an address (actually an OSC address),
	a message string that may be viewed as a method name
	and a list of message parameters.
*/
class Message
{
    public:
        typedef SMARTP<baseparam>		argPtr;		///< a message argument ptr type
        typedef std::vector<argPtr>		argslist;	///< args list type

    private:
        unsigned long	fSrcIP;			///< the message source IP number
        std::string	fAddress;			///< the message osc destination address
        std::string	fAlias;             ///< the message alias osc destination address
        argslist	fArguments;			///< the message arguments

    public:
            /*!
                \brief an empty message constructor
            */
             Message() {}
            /*!
                \brief a message constructor
                \param address the message destination address
            */
            Message(const std::string& address) : fAddress(address), fAlias("") {}
             
            Message(const std::string& address, const std::string& alias) : fAddress(address), fAlias(alias) {}
            /*!
                \brief a message constructor
                \param address the message destination address
                \param args the message parameters
            */
            Message(const std::string& address, const argslist& args) 
                : fAddress(address), fArguments(args) {}
            /*!
                \brief a message constructor
                \param msg a message
            */
             Message(const Message& msg);
    virtual ~Message() {} //{ freed++; std::cout << "running messages: " << (allocated - freed) << std::endl; }

    /*!
        \brief adds a parameter to the message
        \param val the parameter
    */
    template <typename T> void add(T val)	{ fArguments.push_back(new MsgParam<T>(val)); }
    /*!
        \brief adds a float parameter to the message
        \param val the parameter value
    */
    void	add(float val)					{ add<float>(val); }
    
    /*!
     \brief adds a double parameter to the message
     \param val the parameter value
     */
    void	add(double val)					{ add<double>(val); }
    
    /*!
        \brief adds an int parameter to the message
        \param val the parameter value
    */
    void	add(int val)					{ add<int>(val); }
    
    /*!
        \brief adds a string parameter to the message
        \param val the parameter value
    */
    void	add(const std::string& val)		{ add<std::string>(val); }

    /*!
        \brief adds a parameter to the message
        \param val the parameter
    */
    void	add(argPtr val)                 { fArguments.push_back( val ); }

    /*!
        \brief sets the message address
        \param addr the address
    */
    void				setSrcIP(unsigned long addr)		{ fSrcIP = addr; }

    /*!
        \brief sets the message address
        \param addr the address
    */
    void				setAddress(const std::string& addr)		{ fAddress = addr; }
    /*!
        \brief print the message
        \param out the output stream
    */
    void				print(std::ostream& out) const;
    /*!
        \brief send the message to OSC
        \param out the OSC output stream
    */
    void				print(OSCStream& out) const;
    /*!
        \brief print message arguments
        \param out the OSC output stream
    */
    void				printArgs(OSCStream& out) const;

    /// \brief gives the message address
    const std::string&	address() const		{ return fAddress; }
    /// \brief gives the message alias
    const std::string&	alias() const		{ return fAlias; }
    /// \brief gives the message parameters list
    const argslist&		params() const		{ return fArguments; }
    /// \brief gives the message parameters list
    argslist&			params()			{ return fArguments; }
    /// \brief gives the message source IP 
    unsigned long		src() const			{ return fSrcIP; }
    /// \brief gives the message parameters count
    int					size() const		{ return (int)fArguments.size(); }

    bool operator == (const Message& other) const;	

    /*!
        \brief gives a message float parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, float& val) const		{ val = params()[i]->value<float>(val); return params()[i]->isType<float>(); }
    
    /*!
     \brief gives a message double parameter
     \param i the parameter index (0 <= i < size())
     \param val on output: the parameter value when the parameter type matches
     \return false when types don't match
     */
    bool	param(int i, double& val) const		{ val = params()[i]->value<double>(val); return params()[i]->isType<double>(); }
    
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, int& val) const		{ val = params()[i]->value<int>(val); return params()[i]->isType<int>(); }
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, unsigned int& val) const		{ val = params()[i]->value<int>(val); return params()[i]->isType<int>(); }
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
        \note a boolean value is handled as integer
    */
    bool	param(int i, bool& val) const		{ int ival = 0; ival = params()[i]->value<int>(ival); val = ival!=0; return params()[i]->isType<int>(); }
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, long int& val) const	{ val = long(params()[i]->value<int>(val)); return params()[i]->isType<int>(); }
    /*!
        \brief gives a message string parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, std::string& val) const { val = params()[i]->value<std::string>(val); return params()[i]->isType<std::string>(); }
};


} // end namespoace

#endif
/************************** BEGIN GUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <assert.h>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/************************** BEGIN ValueConverter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
                            (GRAME, Copyright 2015-2019)

Set of conversion objects used to map user interface values (for example a gui slider
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter

-- ZoneReader are used to implement screencolor metadata

ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter // Identity by default
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) { return x; };
        virtual double faust2ui(double x) { return x; };
};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {
    
    protected:
        
        bool fActive;
        
    public:
        
        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}
        
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;
        
        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }
    
};

//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
    private:
        
        Interpolator fUI2F;
        Interpolator fF2UI;
        
    public:
        
        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) const {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) const { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) const { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/
/************************** BEGIN MetaDataUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <string.h>
#include <assert.h>


static bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
        scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
        scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
        scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
        scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
        scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
        scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
    protected:
        
        std::string                         fGroupTooltip;
        std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
        std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
        std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
        std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
        std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
        std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
        std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
        std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
        std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
        std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
        std::set<FAUSTFLOAT*>               fHiddenSet;          // set of hidden widget zone
        
        void clearMetadata()
        {
            fGuiSize.clear();
            fTooltip.clear();
            fUnit.clear();
            fRadioDescription.clear();
            fMenuDescription.clear();
            fKnobSet.clear();
            fLedSet.clear();
            fNumSet.clear();
            fLogSet.clear();
            fExpSet.clear();
            fHiddenSet.clear();
            fGroupTooltip = "";
        }
        
        /**
         * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
         * (but not those in the middle of the string)
         */
        static std::string rmWhiteSpaces(const std::string& s)
        {
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if ((i != std::string::npos) && (j != std::string::npos)) {
                return s.substr(i, 1+j-i);
            } else {
                return "";
            }
        }
        
        /**
         * Format tooltip string by replacing some white spaces by
         * return characters so that line width doesn't exceed n.
         * Limitation : long words exceeding n are not cut
         */
        std::string formatTooltip(int n, const std::string& tt)
        {
            std::string ss = tt;  // ss string we are going to format
            int lws = 0;          // last white space encountered
            int lri = 0;          // last return inserted
            for (int i = 0; i < (int)tt.size(); i++) {
                if (tt[i] == ' ') lws = i;
                if (((i-lri) >= n) && (lws > lri)) {
                    // insert return here
                    ss[lws] = '\n';
                    lri = lws;
                }
            }
            return ss;
        }
        
    public:
        
        virtual ~MetaDataUI()
        {}
        
        enum Scale {
            kLin,
            kLog,
            kExp
        };
        
        Scale getScale(FAUSTFLOAT* zone)
        {
            if (fLogSet.count(zone) > 0) return kLog;
            if (fExpSet.count(zone) > 0) return kExp;
            return kLin;
        }
        
        bool isKnob(FAUSTFLOAT* zone)
        {
            return fKnobSet.count(zone) > 0;
        }
        
        bool isRadio(FAUSTFLOAT* zone)
        {
            return fRadioDescription.count(zone) > 0;
        }
        
        bool isMenu(FAUSTFLOAT* zone)
        {
            return fMenuDescription.count(zone) > 0;
        }
        
        bool isLed(FAUSTFLOAT* zone)
        {
            return fLedSet.count(zone) > 0;
        }
        
        bool isNumerical(FAUSTFLOAT* zone)
        {
            return fNumSet.count(zone) > 0;
        }
        
        bool isHidden(FAUSTFLOAT* zone)
        {
            return fHiddenSet.count(zone) > 0;
        }
        
        /**
         * Extracts metadata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
         */
        static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
        {
            enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
            int state = kLabel; int deep = 0;
            std::string key, value;
            
            for (unsigned int i = 0; i < fulllabel.size(); i++) {
                char c = fulllabel[i];
                switch (state) {
                    case kLabel :
                        assert(deep == 0);
                        switch (c) {
                            case '\\' : state = kEscape1; break;
                            case '[' : state = kKey; deep++; break;
                            default : label += c;
                        }
                        break;
                        
                    case kEscape1:
                        label += c;
                        state = kLabel;
                        break;
                        
                    case kEscape2:
                        key += c;
                        state = kKey;
                        break;
                        
                    case kEscape3:
                        value += c;
                        state = kValue;
                        break;
                        
                    case kKey:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape2;
                                break;
                                
                            case '[':
                                deep++;
                                key += c;
                                break;
                                
                            case ':':
                                if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    key += c;
                                }
                                break;
                            default : key += c;
                        }
                        break;
                        
                    case kValue:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape3;
                                break;
                                
                            case '[':
                                deep++;
                                value += c;
                                break;
                                
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    value += c;
                                }
                                break;
                            default : value += c;
                        }
                        break;
                        
                    default:
                        std::cerr << "ERROR unrecognized state " << state << std::endl;
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions
         */
        void declare(FAUSTFLOAT* zone, const char* key, const char* value)
        {
            if (zone == 0) {
                // special zone 0 means group metadata
                if (strcmp(key, "tooltip") == 0) {
                    // only group tooltip are currently implemented
                    fGroupTooltip = formatTooltip(30, value);
                } else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
            } else {
                if (strcmp(key, "size") == 0) {
                    fGuiSize[zone] = atof(value);
                }
                else if (strcmp(key, "tooltip") == 0) {
                    fTooltip[zone] = formatTooltip(30, value);
                }
                else if (strcmp(key, "unit") == 0) {
                    fUnit[zone] = value;
                }
                else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
                else if (strcmp(key, "scale") == 0) {
                    if (strcmp(value, "log") == 0) {
                        fLogSet.insert(zone);
                    } else if (strcmp(value, "exp") == 0) {
                        fExpSet.insert(zone);
                    }
                }
                else if (strcmp(key, "style") == 0) {
                    if (strcmp(value, "knob") == 0) {
                        fKnobSet.insert(zone);
                    } else if (strcmp(value, "led") == 0) {
                        fLedSet.insert(zone);
                    } else if (strcmp(value, "numerical") == 0) {
                        fNumSet.insert(zone);
                    } else {
                        const char* p = value;
                        if (parseWord(p, "radio")) {
                            fRadioDescription[zone] = std::string(p);
                        } else if (parseWord(p, "menu")) {
                            fMenuDescription[zone] = std::string(p);
                        }
                    }
                }
            }
        }
    
};

#endif
/**************************  END  MetaDataUI.h **************************/
/************************** BEGIN ring-buffer.h **************************/
/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
# pragma warning (disable: 4334)
#else
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

static ringbuffer_t *ringbuffer_create(size_t sz);
static void ringbuffer_free(ringbuffer_t *rb);
static void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
static void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
static size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
static size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
static void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_read_space(const ringbuffer_t *rb);
static int ringbuffer_mlock(ringbuffer_t *rb);
static void ringbuffer_reset(ringbuffer_t *rb);
static void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
static size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
static void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two. */

static ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

static void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

static int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading. This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

static size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing. This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

static size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader. Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance. Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

static size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer. Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

static void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

static void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader. `vec' is an array of two places. Set
   the values at `vec' to hold the current readable data at `rb'. If
   the readable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer. `vec' is an array of two places. Set
   the values at `vec' to hold the current writeable data at `rb'. If
   the writeable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__
/**************************  END  ring-buffer.h **************************/

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone)
    {
        assert(ui);
        assert(zone);
    }
    
    virtual ~uiItemBase()
    {}
    
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    virtual double cache() = 0;
    virtual void reflectZone() = 0;
};

// Declared as 'static' to avoid code duplication at link time
static void deleteClist(clist* cl);

struct clist : public std::list<uiItemBase*>
{
    
    virtual ~clist()
    {
        deleteClist(this);
    }
        
};

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data);

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*> fGuiList;
        zmap fZoneMap;
        bool fStopped;
        
     public:
            
        GUI():fStopped(false)
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all items
            for (auto& it : fZoneMap) {
                delete it.second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItemBase* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        }
 
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* cl = fZoneMap[z];
            for (auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        static void runAllGuis()
        {
            for (auto& g : fGuiList) {
                g->run();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        virtual void show() {};	
        virtual bool run() { return false; };

        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {};
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition
 */

template <typename REAL>
class uiTypedItem : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItem(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItem()
        {}
    
        void modifyZone(REAL v)
        {
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
    
        double cache() { return fCache; }
    
};

class uiItem : public uiTypedItem<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItem<FAUSTFLOAT>(ui, zone)
        {}

    public:

        virtual ~uiItem() 
        {}

		void modifyZone(FAUSTFLOAT v)
		{
			fCache = v;
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

};

/**
 * Base class for items with a converter
 */

struct uiConverter {
    
    ValueConverter* fConverter;
    
    uiConverter(MetaDataUI::Scale scale, FAUSTFLOAT umin, FAUSTFLOAT umax, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        // Select appropriate converter according to scale mode
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(umin, umax, fmin, fmax);
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(umin, umax, fmin, fmax);
        } else {
            fConverter = new LinearValueConverter(umin, umax, fmin, fmax);
        }
    }
    
    virtual ~uiConverter()
    {
        delete fConverter;
    }
};

/**
 * User Interface item owned (and so deleted) by external code
 */

class uiOwnedItem : public uiItem {
    
    protected:
    
        uiOwnedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
    
     public:
    
        virtual ~uiOwnedItem()
        {}
    
        virtual void reflectZone() {}
};

/**
 * Callback Item
 */

class uiCallbackItem : public uiItem {
    
    protected:
    
        uiCallback fCallback;
        void* fData;
    
    public:
    
        uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
        : uiItem(ui, zone), fCallback(foo), fData(data) {}
        
        virtual void reflectZone() 
        {		
            FAUSTFLOAT v = *fZone;
            fCache = v; 
            fCallback(v, fData);	
        }
};

/**
 *  For timestamped control
 */

struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items
 */

class uiTimedItem : public uiItem
{
    
    protected:
        
        bool fDelete;
        
    public:
    
        using uiItem::modifyZone;
        
        uiTimedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiTimedItem()
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }
        
        virtual void modifyZone(double date, FAUSTFLOAT v)
        {
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                std::cerr << "ringbuffer_write error DatedControl" << std::endl;
            }
        }
    
};

/**
 * Allows to group a set of zones
 */

class uiGroupItem : public uiItem
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            for (auto& it : fZoneMap) {
                *it = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Can not be defined as method in the classes

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    for (auto& it : *cl) {
        // This specific code is only used in JUCE context. TODO: use proper 'shared_ptr' based memory management.
    #if defined(JUCE_32BIT) || defined(JUCE_64BIT)
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    #else
        delete it;
    #endif
    }
}

#endif
/**************************  END  GUI.h **************************/
/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __RootNode__
#define __RootNode__

#include <map>
#include <string>
#include <vector>

/************************** BEGIN JSONUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>


/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

template <typename REAL>
class JSONUIReal : public PathBuilder, public Meta, public UIReal<REAL>
{

    protected:
    
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fVersion;           // Compiler version
        std::string fCompileOptions;    // Compilation options
        std::vector<std::string> fLibraryList;
        std::vector<std::string> fIncludePathnames;
        std::string fName;
        std::string fFileName;
        std::string fExpandedCode;
        std::string fSHAKey;
        int fDSPSize;                   // In bytes
        std::map<std::string, int> fPathTable;
        bool fExtended;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs, fSRIndex;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::string dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    default:
                        dst += src[i];
                        break;
                }
            }
            return dst;
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
    
        int getAddressIndex(const std::string& path)
        {
            return (fPathTable.find(path) != fPathTable.end()) ? fPathTable[path] : -1;
        }
      
     public:
     
        JSONUIReal(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table);
        }

        JSONUIReal(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }

        JSONUIReal(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
        
        JSONUIReal()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
 
        virtual ~JSONUIReal() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        void setSRIndex(int sr_index) { fSRIndex = sr_index; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table,
                  bool extended = false)
        {
            fTab = 1;
            fExtended = extended;
            if (fExtended) {
                fUI << std::setprecision(std::numeric_limits<REAL>::max_digits10);
                fMeta << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            
            // Start Meta generation
            fMeta.str("");
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            fUI.str("");
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fFileName = filename;
            fInputs = inputs;
            fOutputs = outputs;
            fSRIndex = sr_index;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            pushLabel(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            popLabel();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
  
        virtual void addGenericButton(const char* label, const char* name)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab, false);
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, REAL init, REAL min, REAL max, REAL step)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"init\": " << init << ",";
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max << ",";
            tab(fTab, fUI); fUI << "\"step\": " << step;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, REAL min, REAL max) 
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addSoundfile(const char* label, const char* url, Soundfile** zone)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path);
            }
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        // -- metadata declarations

        virtual void declare(REAL* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            // fName found in metadata
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            // fFileName found in metadata
            if ((strcmp(key, "filename") == 0) && (fFileName == "")) fFileName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            std::stringstream JSON;
            if (fExtended) {
                JSON << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            JSON << "{";
            fTab += 1;
            tab(fTab, JSON); JSON << "\"name\": \"" << fName << "\",";
            tab(fTab, JSON); JSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, JSON); JSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, JSON); JSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    JSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    JSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fDSPSize != -1) { tab(fTab, JSON); JSON << "\"size\": " << fDSPSize << ","; }
            if (fSHAKey != "") { tab(fTab, JSON); JSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, JSON); JSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, JSON); JSON << "\"inputs\": " << fInputs << ",";
            tab(fTab, JSON); JSON << "\"outputs\": " << fOutputs << ",";
            if (fSRIndex != -1) { tab(fTab, JSON); JSON << "\"sr_index\": " << fSRIndex << ","; }
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                JSON << fMeta.str() << fUI.str();
            } else {
                JSON << fUI.str();
            }
            tab(fTab, JSON); JSON << "}";
            return (flat) ? flatten(JSON.str()) : JSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

struct JSONUI : public JSONUIReal<FAUSTFLOAT>, public UI
{
    
    JSONUI(const std::string& name,
           const std::string& filename,
           int inputs,
           int outputs,
           int sr_index,
           const std::string& sha_key,
           const std::string& dsp_code,
           const std::string& version,
           const std::string& compile_options,
           const std::vector<std::string>& library_list,
           const std::vector<std::string>& include_pathnames,
           int size,
           const std::map<std::string, int>& path_table):
    JSONUIReal<FAUSTFLOAT>(name, filename,
                          inputs, outputs,
                          sr_index,
                          sha_key, dsp_code,
                          version, compile_options,
                          library_list, include_pathnames,
                          size, path_table)
    {}
    
    JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
    JSONUIReal<FAUSTFLOAT>(name, filename, inputs, outputs)
    {}
    
    JSONUI(int inputs, int outputs):JSONUIReal<FAUSTFLOAT>(inputs, outputs)
    {}
    
    JSONUI():JSONUIReal<FAUSTFLOAT>()
    {}

    virtual void openTabBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openTabBox(label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openHorizontalBox(label);
    }
    virtual void openVerticalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openVerticalBox(label);
    }
    virtual void closeBox()
    {
        JSONUIReal<FAUSTFLOAT>::closeBox();
    }
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addButton(label, zone);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addCheckButton(label, zone);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
    }
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
    {
        JSONUIReal<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
    }
    
    // -- metadata declarations
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(zone, key, val);
    }

    virtual void declare(const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(key, val);
    }

    virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/

namespace oscfaust
{

class OSCIO;
class RootNode;
typedef class SMARTP<RootNode> SRootNode;

/**
 * an alias target includes a map to rescale input values to output values
 * and a target osc address. The input values can be given in reversed order
 * to reverse the control
 */
struct aliastarget
{
	double      fMinIn;
	double      fMaxIn;
	double      fMinOut;
	double      fMaxOut;
	std::string fTarget;	// the real osc address

	aliastarget(const char* address, double imin, double imax, double omin, double omax)
		: fMinIn(imin), fMaxIn(imax), fMinOut(omin), fMaxOut(omax), fTarget(address) {}

	aliastarget(const aliastarget& t)
		: fMinIn(t.fMinIn), fMaxIn(t.fMaxIn), fMinOut(t.fMinOut), fMaxOut(t.fMaxOut), fTarget(t.fTarget) {}

	double scale(double x) const 
    {
        if (fMinIn < fMaxIn) {
            // increasing control
            double z = (x < fMinIn) ? fMinIn : (x > fMaxIn) ? fMaxIn : x;
            return fMinOut + (z-fMinIn)*(fMaxOut-fMinOut)/(fMaxIn-fMinIn);
            
        } else if (fMinIn > fMaxIn) {
            // reversed control
            double z = (x < fMaxIn) ? fMaxIn : (x > fMinIn) ? fMinIn : x;
            return fMinOut + (fMinIn-z)*(fMaxOut-fMinOut)/(fMinIn-fMaxIn);
            
        } else {
            // no control !
            return (fMinOut+fMaxOut)/2.0f;
        }
    }
    
    double invscale(double x) const
    {
        if (fMinOut < fMaxOut) {
            // increasing control
            double z = (x < fMinOut) ? fMinOut : (x > fMaxOut) ? fMaxOut : x;
            return fMinIn + (z-fMinOut)*(fMaxIn-fMinIn)/(fMaxOut-fMinOut);
            
        } else if (fMinOut > fMaxOut) {
            // reversed control
            double z = (x < fMaxOut) ? fMaxOut : (x > fMinOut) ? fMinOut : x;
            return fMinIn + (fMinOut-z)*(fMaxIn-fMinIn)/(fMinOut-fMaxOut);
            
        } else {
            // no control !
            return (fMinIn+fMaxIn)/2.0f;
        }
    }
};

//--------------------------------------------------------------------------
/*!
	\brief a faust root node

	A Faust root node handles the \c 'hello' message and provides support
	for incoming osc signal data. 
*/
class RootNode : public MessageDriven
{

    private:
        int *fUPDIn, *fUDPOut, *fUDPErr;    // the osc port numbers (required by the hello method)
        OSCIO* fIO;                         // an OSC IO controler
        JSONUI* fJSON;

        typedef std::map<std::string, std::vector<aliastarget> > TAliasMap;
        TAliasMap fAliases;

        template <typename T>
        void processAliasAux(const std::string& address, T val);
        void processAlias(const std::string& address, float val);
        void processAlias(const std::string& address, double val);
    
        void eraseAliases(const std::string& target);
        void eraseAlias(const std::string& target, const std::string& alias);
        bool aliasError(const Message* msg);

    protected:
        RootNode(const char *name, JSONUI* json, OSCIO* io = NULL) : MessageDriven(name, ""), fUPDIn(0), fUDPOut(0), fUDPErr(0), fIO(io), fJSON(json) {}
        virtual ~RootNode() {}

    public:
        static SRootNode create(const char* name, JSONUI* json, OSCIO* io = NULL) { return new RootNode(name, json, io); }

        virtual void processMessage(const Message* msg);
        virtual bool accept(const Message* msg);
        virtual void get(unsigned long ipdest) const;
        virtual void get(unsigned long ipdest, const std::string& what) const;

        template <typename T>
        bool aliasMsgAux(const Message* msg, T omin, T omax);
        bool aliasMsg(const Message* msg, double omin, double omax);
        bool aliasMsg(const Message* msg, float omin, float omax);
    
        template <typename T>
        void addAliasAux(const char* alias, const char* address, T imin, T imax, T omin, T omax);
        void addAlias(const char* alias, const char* address, float imin, float imax, float omin, float omax);
        void addAlias(const char* alias, const char* address, double imin, double imax, double omin, double omax);
    
        bool acceptSignal(const Message* msg);      ///< handler for signal data
        void hello(unsigned long ipdest) const;     ///< handler for the 'hello' message
        void setPorts(int* in, int* out, int* err);

        std::vector<std::pair<std::string, double> > getAliases(const std::string& address, double value);
};

} // end namespoace

#endif

namespace oscfaust
{

/**
 * map (rescale) input values to output values
 */
template <typename C> struct mapping
{
	const C fMinOut;
	const C fMaxOut;
	mapping(C omin, C omax) : fMinOut(omin), fMaxOut(omax) {}
	C clip (C x) { return (x < fMinOut) ? fMinOut : (x > fMaxOut) ? fMaxOut : x; }
};

//--------------------------------------------------------------------------
/*!
	\brief a faust node is a terminal node and represents a faust parameter controler
*/
template <typename C> class FaustNode : public MessageDriven, public uiTypedItem<C>
{
	mapping<C>	fMapping;
    RootNode*   fRoot;
    bool        fInput;  // true for input nodes (slider, button...)
	
	//---------------------------------------------------------------------
	// Warning !!!
	// The cast (C*)fZone is necessary because the real size allocated is
	// only known at execution time. When the library is compiled, fZone is
	// uniquely defined by FAUSTFLOAT.
	//---------------------------------------------------------------------
	bool store(C val) { *(C*)this->fZone = fMapping.clip(val); return true; }
	void sendOSC() const;

	protected:
		FaustNode(RootNode* root, const char *name, C* zone, C init, C min, C max, const char* prefix, GUI* ui, bool initZone, bool input) 
			: MessageDriven(name, prefix), uiTypedItem<C>(ui, zone), fMapping(min, max), fRoot(root), fInput(input)
			{
                if (initZone) {
                    *zone = init; 
                }
            }
			
		virtual ~FaustNode() {}

	public:
		typedef SMARTP<FaustNode<C> > SFaustNode;
		static SFaustNode create(RootNode* root, const char* name, C* zone, C init, C min, C max, const char* prefix, GUI* ui, bool initZone, bool input)	
        { 
            SFaustNode node = new FaustNode(root, name, zone, init, min, max, prefix, ui, initZone, input); 
            /*
                Since FaustNode is a subclass of uiItem, the pointer will also be kept in the GUI class, and it's desallocation will be done there.
                So we don't want to have smartpointer logic desallocate it and we increment the refcount.
            */
            node->addReference();
            return node; 
        }
    
		bool accept(const Message* msg);
		void get(unsigned long ipdest) const;		///< handler for the 'get' message
		virtual void reflectZone() { sendOSC(); this->fCache = *this->fZone; }
};

} // end namespace

#endif

class GUI;
namespace oscfaust
{

class OSCIO;
class RootNode;
typedef class SMARTP<RootNode> SRootNode;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
/*!
	\brief a factory to build a OSC UI hierarchy
	
	Actually, makes use of a stack to build the UI hierarchy.
	It includes a pointer to a OSCIO controler, but just to give it to the root node.
*/
class FaustFactory
{
    std::stack<SMessageDriven>  fNodes;		///< maintains the current hierarchy level
    SRootNode  fRoot;   ///< keep track of the root node
    OSCIO*     fIO;     ///< hack to support audio IO via OSC, actually the field is given to the root node
    GUI*       fGUI;    ///< a GUI pointer to support updateAllGuis(), required for bi-directionnal OSC
    JSONUI*    fJSON;
    
    private:
        std::string addressFirst(const std::string& address) const;
        std::string addressTail(const std::string& address) const;
        
    public:
        FaustFactory(GUI* ui, JSONUI* json, OSCIO * io = NULL);
        virtual ~FaustFactory();
        
        template <typename C> void addnode(const char* label, C* zone, C init, C min, C max, bool initZone, bool input);
        template <typename C> void addAlias(const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max, const char* label);
        
        void addAlias(const char* alias, const char* address, float imin, float imax, float omin, float omax);
        void addAlias(const char* alias, const char* address, double imin, double imax, double omin, double omax);
        void opengroup(const char* label);
        void closegroup();
        
        SRootNode root() const; 
};

/**
 * Add a node to the OSC UI tree in the current group at the top of the stack 
 */
template <typename C> void FaustFactory::addnode(const char* label, C* zone, C init, C min, C max, bool initZone, bool input) 
{
	SMessageDriven top;
	if (fNodes.size()) top = fNodes.top();
	if (top) {
		std::string prefix = top->getOSCAddress();
		top->add(FaustNode<C>::create(root(), label, zone, init, min, max, prefix.c_str(), fGUI, initZone, input));
	}
}

/**
 * Add an alias (actually stored and handled at root node level
 */
template <typename C> void FaustFactory::addAlias(const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max, const char* label)
{
	std::istringstream 	ss(fullpath);
	std::string 		realpath; 
 
	ss >> realpath >> imin >> imax;
	SMessageDriven top = fNodes.top();
	if (top) {
		std::string target = top->getOSCAddress() + "/" + label;
		addAlias(realpath.c_str(), target.c_str(), C(imin), C(imax), C(min), C(max));
	}
}

} // end namespoace

#endif

class GUI;

typedef void (*ErrorCallback)(void*);  

namespace oscfaust
{

class OSCIO;
class OSCSetup;
class OSCRegexp;
    
//--------------------------------------------------------------------------
/*!
	\brief the main Faust OSC Lib API
	
	The OSCControler is essentially a glue between the memory representation (in charge of the FaustFactory),
	and the network services (in charge of OSCSetup).
*/
class OSCControler
{
	int fUDPPort,   fUDPOut, fUPDErr;	// the udp ports numbers
	std::string     fDestAddress;		// the osc messages destination address, used at initialization only
										// to collect the address from the command line
	std::string     fBindAddress;		// when non empty, the address used to bind the socket for listening
	OSCSetup*		fOsc;				// the network manager (handles the udp sockets)
	OSCIO*			fIO;				// hack for OSC IO support (actually only relayed to the factory)
	FaustFactory*	fFactory;			// a factory to build the memory representation

    bool            fInit;
    
	public:
		/*
			base udp port is chosen in an unassigned range from IANA PORT NUMBERS (last updated 2011-01-24)
			see at http://www.iana.org/assignments/port-numbers
			5507-5552  Unassigned
		*/
		enum { kUDPBasePort = 5510 };
            
        OSCControler(int argc, char* argv[], GUI* ui, JSONUI* json, OSCIO* io = NULL, ErrorCallback errCallback = NULL, void* arg = NULL, bool init = true);

        virtual ~OSCControler();
	
		//--------------------------------------------------------------------------
		// addnode, opengroup and closegroup are simply relayed to the factory
		//--------------------------------------------------------------------------
		// Add a node in the current group (top of the group stack)
		template <typename T> void addnode(const char* label, T* zone, T init, T min, T max, bool input = true)
							{ fFactory->addnode(label, zone, init, min, max, fInit, input); }
		
		//--------------------------------------------------------------------------
		// This method is used for alias messages. The arguments imin and imax allow
		// to map incomming values from the alias input range to the actual range 
		template <typename T> void addAlias(const std::string& fullpath, T* zone, T imin, T imax, T init, T min, T max, const char* label)
							{ fFactory->addAlias(fullpath, zone, imin, imax, init, min, max, label); }

		void opengroup(const char* label)		{ fFactory->opengroup(label); }
		void closegroup()						{ fFactory->closegroup(); }
	   
		//--------------------------------------------------------------------------
		void run();				// starts the network services
		void endBundle();		// when bundle mode is on, close and send the current bundle (if any)
		void stop();			// stop the network services
		std::string getInfos() const; // gives information about the current environment (version, port numbers,...)

		int	getUDPPort() const			{ return fUDPPort; }
		int	getUDPOut()	const			{ return fUDPOut; }
		int	getUDPErr()	const			{ return fUPDErr; }
		const char*	getDestAddress() const { return fDestAddress.c_str(); }
		const char*	getRootName() const;	// probably useless, introduced for UI extension experiments
    
        void setUDPPort(int port) { fUDPPort = port; }
        void setUDPOut(int port) { fUDPOut = port; }
        void setUDPErr(int port) { fUPDErr = port; }
        void setDestAddress(const char* address) { fDestAddress = address; }

        // By default, an osc interface emits all parameters. You can filter specific params dynamically.
        static std::vector<OSCRegexp*>     fFilteredPaths; // filtered paths will not be emitted
        static void addFilteredPath(std::string path);
        static bool isPathFiltered(std::string path);
        static void resetFilteredPaths();
    
		static float version();				// the Faust OSC library version number
		static const char* versionstr();	// the Faust OSC library version number as a string
		static int gXmit;                   // a static variable to control the transmission of values
                                            // i.e. the use of the interface as a controler
		static int gBundle;                 // a static variable to control the osc bundle mode
};

#define kNoXmit     0
#define kAll        1
#define kAlias      2

}

#endif

#ifdef _WIN32
#define strcasecmp _stricmp
#endif

/******************************************************************************
 *******************************************************************************
 
 OSC (Open Sound Control) USER INTERFACE
 
 *******************************************************************************
 *******************************************************************************/
/*
 
 Note about the OSC addresses and the Faust UI names:
 ----------------------------------------------------
 There are potential conflicts between the Faust UI objects naming scheme and
 the OSC address space. An OSC symbolic names is an ASCII string consisting of
 printable characters other than the following:
	space
 #	number sign
 *	asterisk
 ,	comma
 /	forward
 ?	question mark
 [	open bracket
 ]	close bracket
 {	open curly brace
 }	close curly brace
 
 a simple solution to address the problem consists in replacing
 space or tabulation with '_' (underscore)
 all the other osc excluded characters with '-' (hyphen)
 
 This solution is implemented in the proposed OSC UI;
 */

class OSCUI : public GUI
{
    
    private:
        
        oscfaust::OSCControler*	fCtrl;
        std::vector<const char*> fAlias;
        JSONUI fJSON;
        
        const char* tr(const char* label) const
        {
            static char buffer[1024];
            char * ptr = buffer; int n=1;
            while (*label && (n++ < 1024)) {
                switch (*label) {
                    case ' ': case '	':
                        *ptr++ = '_';
                        break;
                    case '#': case '*': case ',': case '/': case '?':
                    case '[': case ']': case '{': case '}': case '(': case ')':
                        *ptr++ = '_';
                        break;
                    default:
                        *ptr++ = *label;
                }
                label++;
            }
            *ptr = 0;
            return buffer;
        }
        
        // add all accumulated alias
        void addalias(FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, const char* label)
        {
            for (unsigned int i = 0; i < fAlias.size(); i++) {
                fCtrl->addAlias(fAlias[i], zone, FAUSTFLOAT(0), FAUSTFLOAT(1), init, min, max, label);
            }
            fAlias.clear();
        }
        
    public:
        
        OSCUI(const char* /*applicationname*/, int argc, char* argv[], oscfaust::OSCIO* io = NULL, ErrorCallback errCallback = NULL, void* arg = NULL, bool init = true) : GUI()
        {
            fCtrl = new oscfaust::OSCControler(argc, argv, this, &fJSON, io, errCallback, arg, init);
            //		fCtrl->opengroup(applicationname);
        }
        
        virtual ~OSCUI() { delete fCtrl; }
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)          { fCtrl->opengroup(tr(label)); fJSON.openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fCtrl->opengroup(tr(label)); fJSON.openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fCtrl->opengroup(tr(label)); fJSON.openVerticalBox(label); }
        virtual void closeBox()                             { fCtrl->closegroup(); fJSON.closeBox(); }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            const char* l = tr(label);
            addalias(zone, 0, 0, 1, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(1));
            fJSON.addButton(label, zone);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            const char* l = tr(label);
            addalias(zone, 0, 0, 1, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(1));
            fJSON.addCheckButton(label, zone);
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            const char* l = tr(label);
            addalias(zone, init, min, max, l);
            fCtrl->addnode(l, zone, init, min, max);
            fJSON.addVerticalSlider(label, zone, init, min, max, step);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            const char* l = tr(label);
            addalias(zone, init, min, max, l);
            fCtrl->addnode(l, zone, init, min, max);
            fJSON.addHorizontalSlider(label, zone, init, min, max, step);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            const char* l = tr(label);
            addalias(zone, init, min, max, l);
            fCtrl->addnode(l, zone, init, min, max);
            fJSON.addNumEntry(label, zone, init, min, max, step);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            const char* l = tr(label);
            addalias(zone, 0, min, max, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), min, max, false);
            fJSON.addHorizontalBargraph(label, zone, min, max);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            const char* l = tr(label);
            addalias(zone, 0, min, max, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), min, max, false);
            fJSON.addVerticalBargraph(label, zone, min, max);
        }
            
        // -- metadata declarations
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* alias)
        {
            if (strcasecmp(key, "OSC") == 0) fAlias.push_back(alias);
            fJSON.declare(zone, key, alias);
        }
        
        virtual void show() {}
        
        bool run()
        {
            fCtrl->run();
            return true;
        }
        
        void stop()			{ fCtrl->stop(); }
        void endBundle() 	{ fCtrl->endBundle(); }
        
        std::string getInfos()          { return fCtrl->getInfos(); }
        
        const char* getRootName()		{ return fCtrl->getRootName(); }
        int getUDPPort()                { return fCtrl->getUDPPort(); }
        int getUDPOut()                 { return fCtrl->getUDPOut(); }
        int getUDPErr()                 { return fCtrl->getUDPErr(); }
        const char* getDestAddress()    { return fCtrl->getDestAddress(); }
        
        void setUDPPort(int port)       { fCtrl->setUDPPort(port); }
        void setUDPOut(int port)        { fCtrl->setUDPOut(port); }
        void setUDPErr(int port)        { fCtrl->setUDPErr(port); }
        void setDestAddress(const char* address)    { return fCtrl->setDestAddress(address); }
    
};

#endif // __OSCUI__
/**************************  END  OSCUI.h **************************/

#ifdef POLY2
#include "effect.h"
#endif

#if SOUNDFILE
/************************** BEGIN SoundUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __SoundUI_H__
#define __SoundUI_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>


#if defined(__APPLE__) && !defined(__VCVRACK__)
#include <CoreFoundation/CFBundle.h>
#endif

// Always included otherwise -i mode later on will not always include it (with the conditional includes)
/************************** BEGIN Soundfile.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __Soundfile__
#define __Soundfile__

#include <iostream>
#include <string.h>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define BUFFER_SIZE 16384
#define SAMPLE_RATE 44100
#define MAX_CHAN 64
#define MAX_SOUNDFILE_PARTS 256

#ifdef _MSC_VER
#define PRE_PACKED_STRUCTURE __pragma(pack(push, 1))
#define POST_PACKED_STRUCTURE \
    ;                         \
    __pragma(pack(pop))
#else
#define PRE_PACKED_STRUCTURE
#define POST_PACKED_STRUCTURE __attribute__((__packed__))
#endif

/*
 The soundfile structure to be used by the DSP code. Soundfile has a MAX_SOUNDFILE_PARTS parts 
 (even a single soundfile or an empty soundfile). 
 fLength, fOffset and fSR fields are filled accordingly by repeating
 the actual parts if needed.
 
 It has to be 'packed' to that the LLVM backend can correctly access it.

 Index computation:
    - p is the current part number [0..MAX_SOUNDFILE_PARTS-1] (must be proved by the type system)
    - i is the current position in the part. It will be constrained between [0..length]
    - idx(p,i) = fOffset[p] + max(0, min(i, fLength[p]));
*/

PRE_PACKED_STRUCTURE
struct Soundfile {
    FAUSTFLOAT** fBuffers;
    int* fLength;   // length of each part (so fLength[P] contains the length in frames of part P)
    int* fSR;       // sample rate of each part (so fSR[P] contains the SR of part P)
    int* fOffset;   // offset of each part in the global buffer (so fOffset[P] contains the offset in frames of part P)
    int fChannels;  // max number of channels of all concatenated files

    Soundfile()
    {
        fBuffers  = nullptr;
        fChannels = -1;
        fLength   = new int[MAX_SOUNDFILE_PARTS];
        fSR       = new int[MAX_SOUNDFILE_PARTS];
        fOffset   = new int[MAX_SOUNDFILE_PARTS];
    }

    ~Soundfile()
    {
        // Free the real channels only
        for (int chan = 0; chan < fChannels; chan++) {
            delete[] fBuffers[chan];
        }
        delete[] fBuffers;
        delete[] fLength;
        delete[] fSR;
        delete[] fOffset;
    }

} POST_PACKED_STRUCTURE;

/*
 The generic soundfile reader.
 */

class SoundfileReader {
    
   protected:
    
    int fDriverSR;
    
    void emptyFile(Soundfile* soundfile, int part, int& offset)
    {
        soundfile->fLength[part] = BUFFER_SIZE;
        soundfile->fSR[part] = SAMPLE_RATE;
        soundfile->fOffset[part] = offset;
        // Update offset
        offset += soundfile->fLength[part];
    }

    Soundfile* createSoundfile(int cur_chan, int length, int max_chan)
    {
        Soundfile* soundfile = new Soundfile();
        soundfile->fBuffers = new FAUSTFLOAT*[max_chan];
        
        for (int chan = 0; chan < cur_chan; chan++) {
            soundfile->fBuffers[chan] = new FAUSTFLOAT[length];
            memset(soundfile->fBuffers[chan], 0, sizeof(FAUSTFLOAT) * length);
        }
        
        soundfile->fChannels = cur_chan;
        return soundfile;
    }

    void getBuffersOffset(Soundfile* soundfile, FAUSTFLOAT** buffers, int offset)
    {
        for (int chan = 0; chan < soundfile->fChannels; chan++) {
            buffers[chan] = &soundfile->fBuffers[chan][offset];
        }
    }
    
    // Check if a soundfile exists and return its real path_name
    std::string checkFile(const std::vector<std::string>& sound_directories, const std::string& file_name)
    {
        if (checkFile(file_name)) {
            return file_name;
        } else {
            for (size_t i = 0; i < sound_directories.size(); i++) {
                std::string path_name = sound_directories[i] + "/" + file_name;
                if (checkFile(path_name)) { return path_name; }
            }
            return "";
        }
    }
    
    bool isResampling(int sample_rate) { return (fDriverSR > 0 && fDriverSR != sample_rate); }
 
    // To be implemented by subclasses

    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    virtual bool checkFile(const std::string& path_name) = 0;
    
    /**
     * Check the availability of a sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     *
     * @return true if the sound resource is available, false otherwise.
     */

    virtual bool checkFile(unsigned char* buffer, size_t size) { return true; }

    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length) = 0;
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(unsigned char* buffer, size_t size, int& channels, int& length) {}

    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan) = 0;
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, unsigned char* buffer, size_t size, int part, int& offset, int max_chan) {}

  public:
    
    virtual ~SoundfileReader() {}
    
    void setSampleRate(int sample_rate) { fDriverSR = sample_rate; }
   
    Soundfile* createSoundfile(const std::vector<std::string>& path_name_list, int max_chan)
    {
        try {
            int cur_chan = 1; // At least one buffer
            int total_length = 0;
            
            // Compute total length and channels max of all files
            for (int i = 0; i < int(path_name_list.size()); i++) {
                int chan, length;
                if (path_name_list[i] == "__empty_sound__") {
                    length = BUFFER_SIZE;
                    chan = 1;
                } else {
                    getParamsFile(path_name_list[i], chan, length);
                }
                cur_chan = std::max<int>(cur_chan, chan);
                total_length += length;
            }
           
            // Complete with empty parts
            total_length += (MAX_SOUNDFILE_PARTS - path_name_list.size()) * BUFFER_SIZE;
            
            // Create the soundfile
            Soundfile* soundfile = createSoundfile(cur_chan, total_length, max_chan);
            
            // Init offset
            int offset = 0;
            
            // Read all files
            for (int i = 0; i < int(path_name_list.size()); i++) {
                if (path_name_list[i] == "__empty_sound__") {
                    emptyFile(soundfile, i, offset);
                } else {
                    readFile(soundfile, path_name_list[i], i, offset, max_chan);
                }
            }
            
            // Complete with empty parts
            for (int i = int(path_name_list.size()); i < MAX_SOUNDFILE_PARTS; i++) {
                emptyFile(soundfile, i, offset);
            }
            
            // Share the same buffers for all other channels so that we have max_chan channels available
            for (int chan = cur_chan; chan < max_chan; chan++) {
                soundfile->fBuffers[chan] = soundfile->fBuffers[chan % cur_chan];
            }
            
            return soundfile;
            
        } catch (...) {
            return nullptr;
        }
    }

    // Check if all soundfiles exist and return their real path_name
    std::vector<std::string> checkFiles(const std::vector<std::string>& sound_directories,
                                        const std::vector<std::string>& file_name_list)
    {
        std::vector<std::string> path_name_list;
        for (size_t i = 0; i < file_name_list.size(); i++) {
            std::string path_name = checkFile(sound_directories, file_name_list[i]);
            // If 'path_name' is not found, it is replaced by an empty sound (= silence)
            path_name_list.push_back((path_name == "") ? "__empty_sound__" : path_name);
        }
        return path_name_list;
    }

};

#endif
/**************************  END  Soundfile.h **************************/

#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
/************************** BEGIN JuceReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JuceReader__
#define __JuceReader__

#include <assert.h>

#include "../JuceLibraryCode/JuceHeader.h"


struct JuceReader : public SoundfileReader {
    
    juce::AudioFormatManager fFormatManager;
    
    JuceReader() { fFormatManager.registerBasicFormats(); }
    virtual ~JuceReader()
    {}
    
    bool checkFile(const std::string& path_name)
    {
        juce::File file(path_name);
        if (file.existsAsFile()) {
            return true;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "'" << std::endl;
            return false;
        }
    }
    
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        std::unique_ptr<juce::AudioFormatReader> formatReader (fFormatManager.createReaderFor (juce::File (path_name)));
        channels = int(formatReader->numChannels);
        length = int(formatReader->lengthInSamples);
    }
    
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        std::unique_ptr<juce::AudioFormatReader> formatReader (fFormatManager.createReaderFor (juce::File (path_name)));
        
        soundfile->fLength[part] = int(formatReader->lengthInSamples);
        soundfile->fSR[part] = int(formatReader->sampleRate);
        soundfile->fOffset[part] = offset;
        
        FAUSTFLOAT** buffers = static_cast<FAUSTFLOAT**>(alloca(soundfile->fChannels * sizeof(FAUSTFLOAT*)));
                                                             
        getBuffersOffset(soundfile, buffers, offset);
        
        if (formatReader->read(reinterpret_cast<int *const *>(buffers), int(formatReader->numChannels), 0, int(formatReader->lengthInSamples), false)) {
            
            // Possibly concert samples
            if (!formatReader->usesFloatingPointData) {
                for (int chan = 0; chan < int(formatReader->numChannels); ++chan) {
                    FAUSTFLOAT* buffer = &soundfile->fBuffers[chan][soundfile->fOffset[part]];
                    juce::FloatVectorOperations::convertFixedToFloat(buffer, reinterpret_cast<const int*>(buffer), 1.0f/0x7fffffff, int(formatReader->lengthInSamples));
                }
            }
            
        } else {
            std::cerr << "Error reading the file : " << path_name << std::endl;
        }
            
        // Update offset
        offset += soundfile->fLength[part];
    }
    
};

#endif
/**************************  END  JuceReader.h **************************/
JuceReader gReader;
#elif defined(ESP32)
/************************** BEGIN Esp32Reader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_ESP32READER_H
#define FAUST_ESP32READER_H

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

/************************** BEGIN WaveReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __WaveReader__
#define __WaveReader__

#include <string.h>
#include <assert.h>
#include <iostream>


// WAVE file description
typedef struct {
    
    // The canonical WAVE format starts with the RIFF header
    
    /**
     Variable: chunk_id
     Contains the letters "RIFF" in ASCII form (0x52494646 big-endian form).
     **/
    int chunk_id;
    
    /**
     Variable: chunk_size
     36 + SubChunk2Size, or more precisely: 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
     This is the size of the rest of the chunk following this number.
     This is the size of the entire file in bytes minus 8 bytes for the
     two fields not included in this count: ChunkID and ChunkSize.
     **/
    int chunk_size;
    
    /**
     Variable: format
     Contains the letters "WAVE" (0x57415645 big-endian form).
     **/
    int format;
    
    // The "WAVE" format consists of two subchunks: "fmt " and "data":
    // The "fmt " subchunk describes the sound data's format:
    
    /**
     Variable: subchunk_1_id
     Contains the letters "fmt " (0x666d7420 big-endian form).
     **/
    int subchunk_1_id;
    
    /**
     Variable: subchunk_1_size
     16 for PCM. This is the size of the rest of the Subchunk which follows this number.
     **/
    int subchunk_1_size;
    
    /**
     Variable: audio_format
     PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.
     **/
    short audio_format;
    
    /**
     Variable: num_channels
     Mono = 1, Stereo = 2, etc.
     **/
    short num_channels;
    
    /**
     Variable: sample_rate
     8000, 44100, etc.
     **/
    int sample_rate;
    
    /**
     Variable: byte_rate
     == SampleRate * NumChannels * BitsPerSample/8
     **/
    int byte_rate;
    
    /**
     Variable: block_align
     == NumChannels * BitsPerSample/8
     The number of bytes for one sample including all channels. I wonder what happens
     when this number isn't an integer?
     **/
    short block_align;
    
    /**
     Variable: bits_per_sample
     8 bits = 8, 16 bits = 16, etc.
     **/
    short bits_per_sample;
    
    /**
     Here should come some extra parameters which i will avoid.
     **/
    
    // The "data" subchunk contains the size of the data and the actual sound:
    
    /**
     Variable: subchunk_2_id
     Contains the letters "data" (0x64617461 big-endian form).
     **/
    int subchunk_2_id;
    
    /**
     Variable: subchunk_2_size
     == NumSamples * NumChannels * BitsPerSample/8
     This is the number of bytes in the data. You can also think of this as the size
     of the read of the subchunk following this number.
     **/
    int subchunk_2_size;
    
    /**
     Variable: data
     The actual sound data.
     **/
    char* data;
    
} wave_t;

// Base reader
struct Reader {
    
    wave_t* fWave;

    inline int is_big_endian()
    {
        int a = 1;
        return !((char*)&a)[0];
    }
    
    inline int convert_to_int(char* buffer, int len)
    {
        int a = 0;
        if (!is_big_endian()) {
            for(int i = 0; i < len; i++) {
                ((char*)&a)[i] = buffer[i];
            }
        } else {
            for(int i = 0; i < len; i++) {
                ((char*)&a)[3-i] = buffer[i];
            }
        }
        return a;
    }
    
    Reader()
    {
        fWave = (wave_t*)calloc(1, sizeof(wave_t));
    }

    virtual ~Reader()
    {
        free(fWave->data);
        free(fWave);
    }

    bool load_wave_header()
    {
        char buffer[4];
        
        read(buffer, 4);
        if (strncmp(buffer, "RIFF", 4) != 0) {
            std::cerr << "This is not valid WAV file!\n";
            return false;
        }
        fWave->chunk_id = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->chunk_size = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->format = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->subchunk_1_id = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->subchunk_1_size = convert_to_int(buffer, 4);
        
        read(buffer, 2);
        fWave->audio_format = convert_to_int(buffer, 2);
        
        read(buffer, 2);
        fWave->num_channels = convert_to_int(buffer, 2);
        
        read(buffer, 4);
        fWave->sample_rate = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->byte_rate = convert_to_int(buffer, 4);
        
        read(buffer, 2);
        fWave->block_align = convert_to_int(buffer, 2);
        
        read(buffer, 2);
        fWave->bits_per_sample = convert_to_int(buffer, 2);
        
        read(buffer, 4);
        if (strncmp(buffer, "data", 4) != 0) {
            read(buffer, 4);
            int _extra_size = convert_to_int(buffer, 4);
            char _extra_data[_extra_size];
            read(_extra_data, _extra_size);
            read(buffer, 4);
            fWave->subchunk_2_id = convert_to_int(buffer, 4);
        } else {
            fWave->subchunk_2_id = convert_to_int(buffer, 4);
        }
        
        read(buffer, 4);
        fWave->subchunk_2_size = convert_to_int(buffer, 4);
        return true;
    }
    
    void load_wave()
    {
        // Read sound data
        fWave->data = (char*)malloc(fWave->subchunk_2_size);
        read(fWave->data, fWave->subchunk_2_size);
    }

    virtual void read(char* buffer, unsigned int size) = 0;
   
};

struct FileReader : public Reader {
    
    FILE* fFile;
    
    FileReader(const std::string& file_path)
    {
        fFile = fopen(file_path.c_str(), "rb");
        if (!fFile) {
            std::cerr << "FileReader : cannot open file!\n";
            throw -1;
        }
        if (!load_wave_header()) {
            std::cerr << "FileReader : not a WAV file!\n";
            throw -1;
        }
    }
    
    virtual ~FileReader()
    {
        fclose(fFile);
    }
    
    void read(char* buffer, unsigned int size)
    {
        fread(buffer, 1, size, fFile);
    }
    
};

extern const uint8_t file_start[] asm("_binary_FILE_start");
extern const uint8_t file_end[]   asm("_binary_FILE_end");

struct MemoryReader : public Reader {
    
    int fPos;
    const uint8_t* fStart;
    const uint8_t* fEnd;
    
    MemoryReader(const uint8_t* start, const uint8_t* end):fPos(0)
    {
        fStart = start;
        fEnd = end;
        if (!load_wave_header()) {
            std::cerr << "MemoryReader : not a WAV file!\n";
            throw -1;
        }
    }
    
    virtual ~MemoryReader()
    {}
    
    void read(char* buffer, unsigned int size)
    {
        memcpy(buffer, fStart + fPos, size);
        fPos += size;
    }
    
};

// Using a FileReader to implement SoundfileReader

struct WaveReader : public SoundfileReader {
    
    WaveReader() {}
    virtual ~WaveReader() {}
    
    virtual bool checkFile(const std::string& path_name)
    {
        try {
            FileReader reader(path_name);
            return true;
        } catch (...)  {
            return false;
        }
    }
    
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        FileReader reader(path_name);
        channels = reader.fWave->num_channels;
        length = (reader.fWave->subchunk_2_size * 8) / (reader.fWave->num_channels * reader.fWave->bits_per_sample);
    }
    
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        FileReader reader(path_name);
        reader.load_wave();
        
        soundfile->fLength[part] = (reader.fWave->subchunk_2_size * 8) / (reader.fWave->num_channels * reader.fWave->bits_per_sample);
        soundfile->fSR[part] = reader.fWave->sample_rate;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        if (reader.fWave->bits_per_sample == 16) {
            float factor = 1.f/32767.f;
            for (int sample = 0; sample < soundfile->fLength[part]; sample++) {
                short* frame = (short*)&reader.fWave->data[reader.fWave->block_align * sample];
                for (int chan = 0; chan < reader.fWave->num_channels; chan++) {
                    soundfile->fBuffers[chan][offset + sample] = frame[chan] * factor;
                }
            }
        } else if (reader.fWave->bits_per_sample == 32) {
            std::cerr << "readFile : not implemented \n";
        }
        
        // Update offset
        offset += soundfile->fLength[part];
    }
};

#endif
/**************************  END  WaveReader.h **************************/

#define TAG "Esp32Reader"

#define SD_PIN_NUM_MISO GPIO_NUM_2
#define SD_PIN_NUM_MOSI GPIO_NUM_15
#define SD_PIN_NUM_CLK  GPIO_NUM_14
#define SD_PIN_NUM_CS   GPIO_NUM_13

struct Esp32Reader : public WaveReader {
    
    void sdcard_init()
    {
        ESP_LOGI(TAG, "Initializing SD card");
        ESP_LOGI(TAG, "Using SPI peripheral");
        
        sdmmc_host_t host = SDSPI_HOST_DEFAULT();
        sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
        slot_config.gpio_miso = SD_PIN_NUM_MISO;
        slot_config.gpio_mosi = SD_PIN_NUM_MOSI;
        slot_config.gpio_sck  = SD_PIN_NUM_CLK;
        slot_config.gpio_cs   = SD_PIN_NUM_CS;
        // This initializes the slot without card detect (CD) and write protect (WP) signals.
        // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
        
        // Options for mounting the filesystem.
        // If format_if_mount_failed is set to true, SD card will be partitioned and
        // formatted in case when mounting fails.
        esp_vfs_fat_sdmmc_mount_config_t mount_config = {
            .format_if_mount_failed = false,
            .max_files = 5,
            .allocation_unit_size = 16 * 1024
        };
        
        // Use settings defined above to initialize SD card and mount FAT filesystem.
        // Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
        // Please check its source code and implement error recovery when developing
        // production applications.
        sdmmc_card_t* card;
        esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
        
        if (ret != ESP_OK) {
            if (ret == ESP_FAIL) {
                ESP_LOGE(TAG, "Failed to mount filesystem. "
                         "If you want the card to be formatted, set format_if_mount_failed = true.");
            } else {
                ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                         "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
            }
            return;
        }
        
        // Card has been initialized, print its properties
        sdmmc_card_print_info(stdout, card);
        ESP_LOGI(TAG, "SD card initialized");
    }
    
    Esp32Reader()
    {
        sdcard_init();
    }
   
    // Access methods inherited from WaveReader
};

#endif // FAUST_ESP32READER_H
/**************************  END  Esp32Reader.h **************************/
WaveReader gReader;
#elif defined(MEMORY_READER)
/************************** BEGIN MemoryReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __MemoryReader__
#define __MemoryReader__


/*
 A 'MemoryReader' object can be used to prepare a set of sound resources in memory, to be used by SoundUI::addSoundfile.
 
 A Soundfile* object will have to be filled with a list of sound resources: the fLength, fOffset, fSampleRate and fBuffers fields 
 have to be completed with the appropriate values, and will be accessed in the DSP object while running.
 *
 */

// To adapt for a real case use

#define SOUND_CHAN      2
#define SOUND_LENGTH    4096
#define SOUND_SR        44100

struct MemoryReader : public SoundfileReader {
    
    MemoryReader()
    {}
    
    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    virtual bool checkFile(const std::string& path_name) { return true; }
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        channels = SOUND_CHAN;
        length = SOUND_LENGTH;
    }
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        soundfile->fLength[part] = SOUND_LENGTH;
        soundfile->fSR[part] = SOUND_SR;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        for (int sample = 0; sample < SOUND_LENGTH; sample++) {
            for (int chan = 0; chan < SOUND_CHAN; chan++) {
                soundfile->fBuffers[chan][offset + sample] = 0.f;
            }
        }
        
        // Update offset
        offset += SOUND_LENGTH;
    }
    
};

#endif
/**************************  END  MemoryReader.h **************************/
MemoryReader gReader;
#else
/************************** BEGIN LibsndfileReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __LibsndfileReader__
#define __LibsndfileReader__

#ifdef SAMPLERATE
#include <samplerate.h>
#endif
#include <sndfile.h>
#include <string.h>
#include <assert.h>
#include <iostream>


struct VFLibsndfile {
    
    #define SIGNED_SIZEOF(x) ((int)sizeof(x))
    
    unsigned char* fBuffer;
    size_t fLength;
    size_t fOffset;
    SF_VIRTUAL_IO fVIO;
    
    VFLibsndfile(unsigned char* buffer, size_t length):fBuffer(buffer), fLength(length), fOffset(0)
    {
        fVIO.get_filelen = vfget_filelen;
        fVIO.seek = vfseek;
        fVIO.read = vfread;
        fVIO.write = vfwrite;
        fVIO.tell = vftell;
    }
    
    static sf_count_t vfget_filelen(void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        return vf->fLength;
    }
  
    static sf_count_t vfseek(sf_count_t offset, int whence, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        switch (whence) {
            case SEEK_SET:
                vf->fOffset = offset;
                break;
                
            case SEEK_CUR:
                vf->fOffset = vf->fOffset + offset;
                break;
                
            case SEEK_END:
                vf->fOffset = vf->fLength + offset;
                break;
                
            default:
                break;
        };
        
        return vf->fOffset;
    }
    
    static sf_count_t vfread(void* ptr, sf_count_t count, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        
        /*
         **	This will break badly for files over 2Gig in length, but
         **	is sufficient for testing.
         */
        if (vf->fOffset + count > vf->fLength) {
            count = vf->fLength - vf->fOffset;
        }
        
        memcpy(ptr, vf->fBuffer + vf->fOffset, count);
        vf->fOffset += count;
        
        return count;
    }
    
    static sf_count_t vfwrite(const void* ptr, sf_count_t count, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        
        /*
         **	This will break badly for files over 2Gig in length, but
         **	is sufficient for testing.
         */
        if (vf->fOffset >= SIGNED_SIZEOF(vf->fBuffer)) {
            return 0;
        }
        
        if (vf->fOffset + count > SIGNED_SIZEOF(vf->fBuffer)) {
            count = sizeof (vf->fBuffer) - vf->fOffset;
        }
        
        memcpy(vf->fBuffer + vf->fOffset, ptr, (size_t)count);
        vf->fOffset += count;
        
        if (vf->fOffset > vf->fLength) {
            vf->fLength = vf->fOffset;
        }
        
        return count;
    }
    
    static sf_count_t vftell(void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        return vf->fOffset;
    }
 
};

struct LibsndfileReader : public SoundfileReader {
	
    LibsndfileReader() {}
	
    typedef sf_count_t (* sample_read)(SNDFILE* sndfile, FAUSTFLOAT* ptr, sf_count_t frames);
	
    // Check file
    bool checkFile(const std::string& path_name)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        return checkFileAux(snd_file, path_name);
    }
    
    bool checkFile(unsigned char* buffer, size_t length)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, length);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        return checkFileAux(snd_file, "virtual file");
    }
    
    bool checkFileAux(SNDFILE* snd_file, const std::string& path_name)
    {
        if (snd_file) {
            sf_close(snd_file);
            return true;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "' (" << sf_strerror(NULL) << ")" << std::endl;
            return false;
        }
    }

    // Open the file and returns its length and channels
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        getParamsFileAux(snd_file, snd_info, channels, length);
    }
    
    void getParamsFile(unsigned char* buffer, size_t size, int& channels, int& length)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, size);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        getParamsFileAux(snd_file, snd_info, channels, length);
    }
    
    void getParamsFileAux(SNDFILE* snd_file, const SF_INFO& snd_info, int& channels, int& length)
    {
        assert(snd_file);
        channels = int(snd_info.channels);
    #ifdef SAMPLERATE
        length = (isResampling(snd_info.samplerate)) ? ((double(snd_info.frames) * double(fDriverSR) / double(snd_info.samplerate)) + BUFFER_SIZE) : int(snd_info.frames);
    #else
        length = int(snd_info.frames);
    #endif
        sf_close(snd_file);
    }
    
    // Read the file
    void copyToOut(Soundfile* soundfile, int size, int channels, int max_channels, int offset, FAUSTFLOAT* buffer)
    {
        for (int sample = 0; sample < size; sample++) {
            for (int chan = 0; chan < channels; chan++) {
                soundfile->fBuffers[chan][offset + sample] = buffer[sample * max_channels + chan];
            }
        }
    }
    
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        readFileAux(soundfile, snd_file, snd_info, part, offset, max_chan);
    }
    
    void readFile(Soundfile* soundfile, unsigned char* buffer, size_t length, int part, int& offset, int max_chan)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, length);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        readFileAux(soundfile, snd_file, snd_info, part, offset, max_chan);
    }
	
    // Will be called to fill all parts from 0 to MAX_SOUNDFILE_PARTS-1
    void readFileAux(Soundfile* soundfile, SNDFILE* snd_file, const SF_INFO& snd_info, int part, int& offset, int max_chan)
    {
        assert(snd_file);
        int channels = std::min<int>(max_chan, snd_info.channels);
    #ifdef SAMPLERATE
        if (isResampling(snd_info.samplerate)) {
            soundfile->fLength[part] = int(double(snd_info.frames) * double(fDriverSR) / double(snd_info.samplerate));
            soundfile->fSR[part] = fDriverSR;
        } else {
            soundfile->fLength[part] = int(snd_info.frames);
            soundfile->fSR[part] = snd_info.samplerate;
        }
    #else
        soundfile->fLength[part] = int(snd_info.frames);
        soundfile->fSR[part] = snd_info.samplerate;
    #endif
        soundfile->fOffset[part] = offset;
		
        // Read and fill snd_info.channels number of channels
        sf_count_t nbf;
        FAUSTFLOAT* buffer_in = (FAUSTFLOAT*)alloca(BUFFER_SIZE * sizeof(FAUSTFLOAT) * snd_info.channels);
        sample_read reader;
        
        if (sizeof(FAUSTFLOAT) == 4) {
            reader = reinterpret_cast<sample_read>(sf_readf_float);
        } else {
            reader = reinterpret_cast<sample_read>(sf_readf_double);
        }
        
    #ifdef SAMPLERATE
        // Resampling
        SRC_STATE* resampler = nullptr;
        FAUSTFLOAT* buffer_out = nullptr;
        if  (isResampling(snd_info.samplerate)) {
            int error;
            resampler = src_new(SRC_SINC_FASTEST, channels, &error);
            if (error != 0) {
                std::cerr << "ERROR : src_new " << src_strerror(error) << std::endl;
                throw -1;
            }
            buffer_out = (FAUSTFLOAT*)alloca(BUFFER_SIZE * sizeof(FAUSTFLOAT) * snd_info.channels);
        }
    #endif
        
        do {
            nbf = reader(snd_file, buffer_in, BUFFER_SIZE);
        #ifdef SAMPLERATE
            // Resampling
            if  (isResampling(snd_info.samplerate)) {
                int in_offset = 0;
                SRC_DATA src_data;
                src_data.src_ratio = double(fDriverSR)/double(snd_info.samplerate);
                do {
                    src_data.data_in = &buffer_in[in_offset * snd_info.channels];
                    src_data.data_out = buffer_out;
                    src_data.input_frames = nbf - in_offset;
                    src_data.output_frames = BUFFER_SIZE;
                    src_data.end_of_input = (nbf < BUFFER_SIZE);
                    int res = src_process(resampler, &src_data);
                    if (res != 0) {
                        std::cerr << "ERROR : src_process " << src_strerror(res) << std::endl;
                        throw -1;
                    }
                    copyToOut(soundfile, src_data.output_frames_gen, channels, snd_info.channels, offset, buffer_out);
                    in_offset += src_data.input_frames_used;
                    // Update offset
                    offset += src_data.output_frames_gen;
                } while (in_offset < nbf);
            } else {
                copyToOut(soundfile, nbf, channels, snd_info.channels, offset, buffer_in);
                // Update offset
                offset += nbf;
            }
        #else
            copyToOut(soundfile, nbf, channels, snd_info.channels, offset, buffer_in);
            // Update offset
            offset += nbf;
        #endif
        } while (nbf == BUFFER_SIZE);
		
        sf_close(snd_file);
    #ifdef SAMPLERATE
        if (resampler) src_delete(resampler);
    #endif
    }

};

#endif
/**************************  END  LibsndfileReader.h **************************/
LibsndfileReader gReader;
#endif

// To be used by DSP code if no SoundUI is used
std::vector<std::string> path_name_list;
Soundfile* defaultsound = gReader.createSoundfile(path_name_list, MAX_CHAN);

class SoundUI : public GenericUI
{
		
    private:
    
        std::vector<std::string> fSoundfileDir;             // The soundfile directories
        std::map<std::string, Soundfile*> fSoundfileMap;    // Map to share loaded soundfiles
        SoundfileReader* fSoundReader;

     public:
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directory - the base directory to look for files, which paths will be relative to this one
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         *
         * @return the soundfile loader.
         */
        SoundUI(const std::string& sound_directory = "", int sample_rate = -1, SoundfileReader* reader = nullptr)
        {
            fSoundfileDir.push_back(sound_directory);
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader->setSampleRate(sample_rate);
        }
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directories - a vector of base directories to look for files, which paths will be relative to these ones
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         *
         * @return the soundfile loader.
         */
        SoundUI(const std::vector<std::string>& sound_directories, int sample_rate = -1, SoundfileReader* reader = nullptr)
        :fSoundfileDir(sound_directories)
        {
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader->setSampleRate(sample_rate);
        }
    
        virtual ~SoundUI()
        {   
            // Delete all soundfiles
            for (auto& it : fSoundfileMap) {
                delete it.second;
            }
        }

        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
        {
            const char* saved_url = url; // 'url' is consumed by parseMenuList2
            std::vector<std::string> file_name_list;
            
            bool menu = parseMenuList2(url, file_name_list, true);
            // If not a list, we have as single file
            if (!menu) { file_name_list.push_back(saved_url); }
            
            // Parse the possible list
            if (fSoundfileMap.find(saved_url) == fSoundfileMap.end()) {
                // Check all files and get their complete path
                std::vector<std::string> path_name_list = fSoundReader->checkFiles(fSoundfileDir, file_name_list);
                // Read them and create the Soundfile
                Soundfile* sound_file = fSoundReader->createSoundfile(path_name_list, MAX_CHAN);
                if (sound_file) {
                    fSoundfileMap[saved_url] = sound_file;
                } else {
                    // If failure, use 'defaultsound'
                    std::cerr << "addSoundfile : soundfile for " << saved_url << " cannot be created !" << std::endl;
                    *sf_zone = defaultsound;
                    return;
                }
            }
            
            // Get the soundfile
            *sf_zone = fSoundfileMap[saved_url];
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPath());
         *
         * @return the running executable or plugin path.
         */
        static std::string getBinaryPath()
        {
            std::string bundle_path_str;
        #if defined(__APPLE__) && !defined(__VCVRACK__)
            CFURLRef bundle_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
            if (!bundle_ref) { std::cerr << "getBinaryPath CFBundleCopyBundleURL error\n"; return ""; }
      
            UInt8 bundle_path[1024];
            if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 1024)) {
                bundle_path_str = std::string((char*)bundle_path);
            } else {
                std::cerr << "getBinaryPath CFURLGetFileSystemRepresentation error\n";
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPathFrom());
         *
         * @param path - entry point to start getting the path of the running executable or plugin.
         *
         * @return the running executable or plugin path.
         */
        static std::string getBinaryPathFrom(const std::string& path)
        {
            std::string bundle_path_str;
        #if defined(__APPLE__) && !defined(__VCVRACK__)
            CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFStringCreateWithCString(kCFAllocatorDefault, path.c_str(), CFStringGetSystemEncoding()));
            if (!bundle) { std::cerr << "getBinaryPathFrom CFBundleGetBundleWithIdentifier error '" << path << "'" << std::endl; return ""; }
         
            CFURLRef bundle_ref = CFBundleCopyBundleURL(bundle);
            if (!bundle_ref) { std::cerr << "getBinaryPathFrom CFBundleCopyBundleURL error\n"; return ""; }
            
            UInt8 bundle_path[1024];
            if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 1024)) {
                bundle_path_str = std::string((char*)bundle_path);
            } else {
                std::cerr << "getBinaryPathFrom CFURLGetFileSystemRepresentation error\n";
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
};

#endif
/**************************  END  SoundUI.h **************************/
#endif

// For FAUST_CLASS_NAME to be defined
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)
#define FAUST_ADDSOUNDFILE(s,f)

using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class FilDeSoi1PanStereoSIG0 {
	
  public:
	
	int iRec17[2];
	
  public:
	
	int getNumInputsFilDeSoi1PanStereoSIG0() {
		return 0;
	}
	int getNumOutputsFilDeSoi1PanStereoSIG0() {
		return 1;
	}
	int getInputRateFilDeSoi1PanStereoSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRateFilDeSoi1PanStereoSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitFilDeSoi1PanStereoSIG0(int sample_rate) {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec17[l1] = 0;
		}
	}
	
	void fillFilDeSoi1PanStereoSIG0(int count, double* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec17[0] = (iRec17[1] + 1);
			table[i] = std::sin((9.5873799242852573e-05 * double((iRec17[0] + -1))));
			iRec17[1] = iRec17[0];
		}
	}

};

static FilDeSoi1PanStereoSIG0* newFilDeSoi1PanStereoSIG0() { return (FilDeSoi1PanStereoSIG0*)new FilDeSoi1PanStereoSIG0(); }
static void deleteFilDeSoi1PanStereoSIG0(FilDeSoi1PanStereoSIG0* dsp) { delete dsp; }

static double ftbl0FilDeSoi1PanStereoSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS FilDeSoi1PanStereo
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class FilDeSoi1PanStereo : public dsp {
	
 public:
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider1;
	double fRec0[2];
	FAUSTFLOAT fHslider2;
	double fConst2;
	double fRec18[2];
	double fVec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider3;
	double fRec19[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	double fRec20[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	double fRec21[2];
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	double fRec22[2];
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	double fRec23[2];
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	double fRec24[2];
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	double fRec25[2];
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	double fRec26[2];
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fHslider19;
	double fRec27[2];
	FAUSTFLOAT fCheckbox9;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT fHslider21;
	double fRec28[2];
	FAUSTFLOAT fCheckbox10;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT fHslider23;
	double fRec29[2];
	FAUSTFLOAT fCheckbox11;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT fHslider25;
	double fRec30[2];
	FAUSTFLOAT fCheckbox12;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT fHslider27;
	double fRec31[2];
	FAUSTFLOAT fCheckbox13;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT fHslider29;
	double fRec32[2];
	FAUSTFLOAT fCheckbox14;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT fHslider31;
	double fRec33[2];
	FAUSTFLOAT fCheckbox15;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT fHslider33;
	double fRec34[2];
	FAUSTFLOAT fHslider34;
	double fRec35[2];
	FAUSTFLOAT fHslider35;
	double fRec36[2];
	int IOTA;
	double fVec1[1048576];
	double fConst3;
	FAUSTFLOAT fHslider36;
	FAUSTFLOAT fHslider37;
	int iRec37[2];
	double fVec2[2];
	int iRec38[2];
	double fVec3[262144];
	double fConst4;
	FAUSTFLOAT fHslider38;
	FAUSTFLOAT fHslider39;
	FAUSTFLOAT fHslider40;
	double fVec4[2];
	double fConst5;
	double fRec41[2];
	double fRec42[2];
	double fRec40[2];
	double fVec5[2];
	double fRec39[2];
	double fVec6[2];
	double fRec43[2];
	double fVec7[2];
	double fRec44[2];
	double fVec8[2];
	double fRec45[2];
	double fRec1[2];
	FAUSTFLOAT fCheckbox16;
	FAUSTFLOAT fCheckbox17;
	FAUSTFLOAT fCheckbox18;
	FAUSTFLOAT fCheckbox19;
	FAUSTFLOAT fCheckbox20;
	FAUSTFLOAT fCheckbox21;
	FAUSTFLOAT fCheckbox22;
	FAUSTFLOAT fCheckbox23;
	FAUSTFLOAT fCheckbox24;
	FAUSTFLOAT fCheckbox25;
	FAUSTFLOAT fCheckbox26;
	FAUSTFLOAT fCheckbox27;
	FAUSTFLOAT fCheckbox28;
	FAUSTFLOAT fCheckbox29;
	FAUSTFLOAT fCheckbox30;
	FAUSTFLOAT fCheckbox31;
	FAUSTFLOAT fHslider41;
	double fRec46[2];
	double fVec9[1048576];
	FAUSTFLOAT fHslider42;
	int iRec47[2];
	int iRec48[2];
	double fVec10[262144];
	FAUSTFLOAT fHslider43;
	double fRec50[2];
	double fVec11[2];
	double fRec49[2];
	double fVec12[2];
	double fRec51[2];
	double fVec13[2];
	double fRec52[2];
	double fVec14[2];
	double fRec53[2];
	double fRec2[2];
	FAUSTFLOAT fCheckbox32;
	FAUSTFLOAT fCheckbox33;
	FAUSTFLOAT fCheckbox34;
	FAUSTFLOAT fCheckbox35;
	FAUSTFLOAT fCheckbox36;
	FAUSTFLOAT fCheckbox37;
	FAUSTFLOAT fCheckbox38;
	FAUSTFLOAT fCheckbox39;
	FAUSTFLOAT fCheckbox40;
	FAUSTFLOAT fCheckbox41;
	FAUSTFLOAT fCheckbox42;
	FAUSTFLOAT fCheckbox43;
	FAUSTFLOAT fCheckbox44;
	FAUSTFLOAT fCheckbox45;
	FAUSTFLOAT fCheckbox46;
	FAUSTFLOAT fCheckbox47;
	FAUSTFLOAT fHslider44;
	double fRec54[2];
	double fVec15[1048576];
	FAUSTFLOAT fHslider45;
	int iRec55[2];
	int iRec56[2];
	double fVec16[262144];
	FAUSTFLOAT fHslider46;
	double fRec58[2];
	double fVec17[2];
	double fRec57[2];
	double fVec18[2];
	double fRec59[2];
	double fVec19[2];
	double fRec60[2];
	double fVec20[2];
	double fRec61[2];
	double fRec3[2];
	FAUSTFLOAT fCheckbox48;
	FAUSTFLOAT fCheckbox49;
	FAUSTFLOAT fCheckbox50;
	FAUSTFLOAT fCheckbox51;
	FAUSTFLOAT fCheckbox52;
	FAUSTFLOAT fCheckbox53;
	FAUSTFLOAT fCheckbox54;
	FAUSTFLOAT fCheckbox55;
	FAUSTFLOAT fCheckbox56;
	FAUSTFLOAT fCheckbox57;
	FAUSTFLOAT fCheckbox58;
	FAUSTFLOAT fCheckbox59;
	FAUSTFLOAT fCheckbox60;
	FAUSTFLOAT fCheckbox61;
	FAUSTFLOAT fCheckbox62;
	FAUSTFLOAT fCheckbox63;
	FAUSTFLOAT fHslider47;
	double fRec62[2];
	double fVec21[1048576];
	FAUSTFLOAT fHslider48;
	int iRec63[2];
	int iRec64[2];
	double fVec22[262144];
	FAUSTFLOAT fHslider49;
	double fRec66[2];
	double fVec23[2];
	double fRec65[2];
	double fVec24[2];
	double fRec67[2];
	double fVec25[2];
	double fRec68[2];
	double fVec26[2];
	double fRec69[2];
	double fRec4[2];
	FAUSTFLOAT fCheckbox64;
	FAUSTFLOAT fCheckbox65;
	FAUSTFLOAT fCheckbox66;
	FAUSTFLOAT fCheckbox67;
	FAUSTFLOAT fCheckbox68;
	FAUSTFLOAT fCheckbox69;
	FAUSTFLOAT fCheckbox70;
	FAUSTFLOAT fCheckbox71;
	FAUSTFLOAT fCheckbox72;
	FAUSTFLOAT fCheckbox73;
	FAUSTFLOAT fCheckbox74;
	FAUSTFLOAT fCheckbox75;
	FAUSTFLOAT fCheckbox76;
	FAUSTFLOAT fCheckbox77;
	FAUSTFLOAT fCheckbox78;
	FAUSTFLOAT fCheckbox79;
	FAUSTFLOAT fHslider50;
	double fRec70[2];
	double fVec27[1048576];
	FAUSTFLOAT fHslider51;
	int iRec71[2];
	int iRec72[2];
	double fVec28[262144];
	FAUSTFLOAT fHslider52;
	double fRec74[2];
	double fVec29[2];
	double fRec73[2];
	double fVec30[2];
	double fRec75[2];
	double fVec31[2];
	double fRec76[2];
	double fVec32[2];
	double fRec77[2];
	double fRec5[2];
	FAUSTFLOAT fCheckbox80;
	FAUSTFLOAT fCheckbox81;
	FAUSTFLOAT fCheckbox82;
	FAUSTFLOAT fCheckbox83;
	FAUSTFLOAT fCheckbox84;
	FAUSTFLOAT fCheckbox85;
	FAUSTFLOAT fCheckbox86;
	FAUSTFLOAT fCheckbox87;
	FAUSTFLOAT fCheckbox88;
	FAUSTFLOAT fCheckbox89;
	FAUSTFLOAT fCheckbox90;
	FAUSTFLOAT fCheckbox91;
	FAUSTFLOAT fCheckbox92;
	FAUSTFLOAT fCheckbox93;
	FAUSTFLOAT fCheckbox94;
	FAUSTFLOAT fCheckbox95;
	FAUSTFLOAT fHslider53;
	double fRec78[2];
	double fVec33[1048576];
	FAUSTFLOAT fHslider54;
	int iRec79[2];
	int iRec80[2];
	double fVec34[262144];
	FAUSTFLOAT fHslider55;
	double fRec82[2];
	double fVec35[2];
	double fRec81[2];
	double fVec36[2];
	double fRec83[2];
	double fVec37[2];
	double fRec84[2];
	double fVec38[2];
	double fRec85[2];
	double fRec6[2];
	FAUSTFLOAT fCheckbox96;
	FAUSTFLOAT fCheckbox97;
	FAUSTFLOAT fCheckbox98;
	FAUSTFLOAT fCheckbox99;
	FAUSTFLOAT fCheckbox100;
	FAUSTFLOAT fCheckbox101;
	FAUSTFLOAT fCheckbox102;
	FAUSTFLOAT fCheckbox103;
	FAUSTFLOAT fCheckbox104;
	FAUSTFLOAT fCheckbox105;
	FAUSTFLOAT fCheckbox106;
	FAUSTFLOAT fCheckbox107;
	FAUSTFLOAT fCheckbox108;
	FAUSTFLOAT fCheckbox109;
	FAUSTFLOAT fCheckbox110;
	FAUSTFLOAT fCheckbox111;
	FAUSTFLOAT fHslider56;
	double fRec86[2];
	double fVec39[1048576];
	FAUSTFLOAT fHslider57;
	int iRec87[2];
	int iRec88[2];
	double fVec40[262144];
	FAUSTFLOAT fHslider58;
	double fRec90[2];
	double fVec41[2];
	double fRec89[2];
	double fVec42[2];
	double fRec91[2];
	double fVec43[2];
	double fRec92[2];
	double fVec44[2];
	double fRec93[2];
	double fRec7[2];
	FAUSTFLOAT fCheckbox112;
	FAUSTFLOAT fCheckbox113;
	FAUSTFLOAT fCheckbox114;
	FAUSTFLOAT fCheckbox115;
	FAUSTFLOAT fCheckbox116;
	FAUSTFLOAT fCheckbox117;
	FAUSTFLOAT fCheckbox118;
	FAUSTFLOAT fCheckbox119;
	FAUSTFLOAT fCheckbox120;
	FAUSTFLOAT fCheckbox121;
	FAUSTFLOAT fCheckbox122;
	FAUSTFLOAT fCheckbox123;
	FAUSTFLOAT fCheckbox124;
	FAUSTFLOAT fCheckbox125;
	FAUSTFLOAT fCheckbox126;
	FAUSTFLOAT fCheckbox127;
	FAUSTFLOAT fHslider59;
	double fRec94[2];
	double fVec45[1048576];
	FAUSTFLOAT fHslider60;
	int iRec95[2];
	int iRec96[2];
	double fVec46[262144];
	FAUSTFLOAT fHslider61;
	double fRec98[2];
	double fVec47[2];
	double fRec97[2];
	double fVec48[2];
	double fRec99[2];
	double fVec49[2];
	double fRec100[2];
	double fVec50[2];
	double fRec101[2];
	double fRec8[2];
	FAUSTFLOAT fCheckbox128;
	FAUSTFLOAT fCheckbox129;
	FAUSTFLOAT fCheckbox130;
	FAUSTFLOAT fCheckbox131;
	FAUSTFLOAT fCheckbox132;
	FAUSTFLOAT fCheckbox133;
	FAUSTFLOAT fCheckbox134;
	FAUSTFLOAT fCheckbox135;
	FAUSTFLOAT fCheckbox136;
	FAUSTFLOAT fCheckbox137;
	FAUSTFLOAT fCheckbox138;
	FAUSTFLOAT fCheckbox139;
	FAUSTFLOAT fCheckbox140;
	FAUSTFLOAT fCheckbox141;
	FAUSTFLOAT fCheckbox142;
	FAUSTFLOAT fCheckbox143;
	FAUSTFLOAT fHslider62;
	double fRec102[2];
	double fVec51[1048576];
	FAUSTFLOAT fHslider63;
	int iRec103[2];
	int iRec104[2];
	double fVec52[262144];
	FAUSTFLOAT fHslider64;
	double fRec106[2];
	double fVec53[2];
	double fRec105[2];
	double fVec54[2];
	double fRec107[2];
	double fVec55[2];
	double fRec108[2];
	double fVec56[2];
	double fRec109[2];
	double fRec9[2];
	FAUSTFLOAT fCheckbox144;
	FAUSTFLOAT fCheckbox145;
	FAUSTFLOAT fCheckbox146;
	FAUSTFLOAT fCheckbox147;
	FAUSTFLOAT fCheckbox148;
	FAUSTFLOAT fCheckbox149;
	FAUSTFLOAT fCheckbox150;
	FAUSTFLOAT fCheckbox151;
	FAUSTFLOAT fCheckbox152;
	FAUSTFLOAT fCheckbox153;
	FAUSTFLOAT fCheckbox154;
	FAUSTFLOAT fCheckbox155;
	FAUSTFLOAT fCheckbox156;
	FAUSTFLOAT fCheckbox157;
	FAUSTFLOAT fCheckbox158;
	FAUSTFLOAT fCheckbox159;
	FAUSTFLOAT fHslider65;
	double fRec110[2];
	double fVec57[1048576];
	FAUSTFLOAT fHslider66;
	int iRec111[2];
	int iRec112[2];
	double fVec58[262144];
	FAUSTFLOAT fHslider67;
	double fRec114[2];
	double fVec59[2];
	double fRec113[2];
	double fVec60[2];
	double fRec115[2];
	double fVec61[2];
	double fRec116[2];
	double fVec62[2];
	double fRec117[2];
	double fRec10[2];
	FAUSTFLOAT fCheckbox160;
	FAUSTFLOAT fCheckbox161;
	FAUSTFLOAT fCheckbox162;
	FAUSTFLOAT fCheckbox163;
	FAUSTFLOAT fCheckbox164;
	FAUSTFLOAT fCheckbox165;
	FAUSTFLOAT fCheckbox166;
	FAUSTFLOAT fCheckbox167;
	FAUSTFLOAT fCheckbox168;
	FAUSTFLOAT fCheckbox169;
	FAUSTFLOAT fCheckbox170;
	FAUSTFLOAT fCheckbox171;
	FAUSTFLOAT fCheckbox172;
	FAUSTFLOAT fCheckbox173;
	FAUSTFLOAT fCheckbox174;
	FAUSTFLOAT fCheckbox175;
	FAUSTFLOAT fHslider68;
	double fRec118[2];
	double fVec63[1048576];
	FAUSTFLOAT fHslider69;
	int iRec119[2];
	int iRec120[2];
	double fVec64[262144];
	FAUSTFLOAT fHslider70;
	double fRec122[2];
	double fVec65[2];
	double fRec121[2];
	double fVec66[2];
	double fRec123[2];
	double fVec67[2];
	double fRec124[2];
	double fVec68[2];
	double fRec125[2];
	double fRec11[2];
	FAUSTFLOAT fCheckbox176;
	FAUSTFLOAT fCheckbox177;
	FAUSTFLOAT fCheckbox178;
	FAUSTFLOAT fCheckbox179;
	FAUSTFLOAT fCheckbox180;
	FAUSTFLOAT fCheckbox181;
	FAUSTFLOAT fCheckbox182;
	FAUSTFLOAT fCheckbox183;
	FAUSTFLOAT fCheckbox184;
	FAUSTFLOAT fCheckbox185;
	FAUSTFLOAT fCheckbox186;
	FAUSTFLOAT fCheckbox187;
	FAUSTFLOAT fCheckbox188;
	FAUSTFLOAT fCheckbox189;
	FAUSTFLOAT fCheckbox190;
	FAUSTFLOAT fCheckbox191;
	FAUSTFLOAT fHslider71;
	double fRec126[2];
	double fVec69[1048576];
	FAUSTFLOAT fHslider72;
	int iRec127[2];
	int iRec128[2];
	double fVec70[262144];
	FAUSTFLOAT fHslider73;
	double fRec130[2];
	double fVec71[2];
	double fRec129[2];
	double fVec72[2];
	double fRec131[2];
	double fVec73[2];
	double fRec132[2];
	double fVec74[2];
	double fRec133[2];
	double fRec12[2];
	FAUSTFLOAT fCheckbox192;
	FAUSTFLOAT fCheckbox193;
	FAUSTFLOAT fCheckbox194;
	FAUSTFLOAT fCheckbox195;
	FAUSTFLOAT fCheckbox196;
	FAUSTFLOAT fCheckbox197;
	FAUSTFLOAT fCheckbox198;
	FAUSTFLOAT fCheckbox199;
	FAUSTFLOAT fCheckbox200;
	FAUSTFLOAT fCheckbox201;
	FAUSTFLOAT fCheckbox202;
	FAUSTFLOAT fCheckbox203;
	FAUSTFLOAT fCheckbox204;
	FAUSTFLOAT fCheckbox205;
	FAUSTFLOAT fCheckbox206;
	FAUSTFLOAT fCheckbox207;
	FAUSTFLOAT fHslider74;
	double fRec134[2];
	double fVec75[1048576];
	FAUSTFLOAT fHslider75;
	int iRec135[2];
	int iRec136[2];
	double fVec76[262144];
	FAUSTFLOAT fHslider76;
	double fRec138[2];
	double fVec77[2];
	double fRec137[2];
	double fVec78[2];
	double fRec139[2];
	double fVec79[2];
	double fRec140[2];
	double fVec80[2];
	double fRec141[2];
	double fRec13[2];
	FAUSTFLOAT fCheckbox208;
	FAUSTFLOAT fCheckbox209;
	FAUSTFLOAT fCheckbox210;
	FAUSTFLOAT fCheckbox211;
	FAUSTFLOAT fCheckbox212;
	FAUSTFLOAT fCheckbox213;
	FAUSTFLOAT fCheckbox214;
	FAUSTFLOAT fCheckbox215;
	FAUSTFLOAT fCheckbox216;
	FAUSTFLOAT fCheckbox217;
	FAUSTFLOAT fCheckbox218;
	FAUSTFLOAT fCheckbox219;
	FAUSTFLOAT fCheckbox220;
	FAUSTFLOAT fCheckbox221;
	FAUSTFLOAT fCheckbox222;
	FAUSTFLOAT fCheckbox223;
	FAUSTFLOAT fHslider77;
	double fRec142[2];
	double fVec81[1048576];
	FAUSTFLOAT fHslider78;
	int iRec143[2];
	int iRec144[2];
	double fVec82[262144];
	FAUSTFLOAT fHslider79;
	double fRec146[2];
	double fVec83[2];
	double fRec145[2];
	double fVec84[2];
	double fRec147[2];
	double fVec85[2];
	double fRec148[2];
	double fVec86[2];
	double fRec149[2];
	double fRec14[2];
	FAUSTFLOAT fCheckbox224;
	FAUSTFLOAT fCheckbox225;
	FAUSTFLOAT fCheckbox226;
	FAUSTFLOAT fCheckbox227;
	FAUSTFLOAT fCheckbox228;
	FAUSTFLOAT fCheckbox229;
	FAUSTFLOAT fCheckbox230;
	FAUSTFLOAT fCheckbox231;
	FAUSTFLOAT fCheckbox232;
	FAUSTFLOAT fCheckbox233;
	FAUSTFLOAT fCheckbox234;
	FAUSTFLOAT fCheckbox235;
	FAUSTFLOAT fCheckbox236;
	FAUSTFLOAT fCheckbox237;
	FAUSTFLOAT fCheckbox238;
	FAUSTFLOAT fCheckbox239;
	FAUSTFLOAT fHslider80;
	double fRec150[2];
	double fVec87[1048576];
	FAUSTFLOAT fHslider81;
	int iRec151[2];
	int iRec152[2];
	double fVec88[262144];
	FAUSTFLOAT fHslider82;
	double fRec154[2];
	double fVec89[2];
	double fRec153[2];
	double fVec90[2];
	double fRec155[2];
	double fVec91[2];
	double fRec156[2];
	double fVec92[2];
	double fRec157[2];
	double fRec15[2];
	FAUSTFLOAT fCheckbox240;
	FAUSTFLOAT fCheckbox241;
	FAUSTFLOAT fCheckbox242;
	FAUSTFLOAT fCheckbox243;
	FAUSTFLOAT fCheckbox244;
	FAUSTFLOAT fCheckbox245;
	FAUSTFLOAT fCheckbox246;
	FAUSTFLOAT fCheckbox247;
	FAUSTFLOAT fCheckbox248;
	FAUSTFLOAT fCheckbox249;
	FAUSTFLOAT fCheckbox250;
	FAUSTFLOAT fCheckbox251;
	FAUSTFLOAT fCheckbox252;
	FAUSTFLOAT fCheckbox253;
	FAUSTFLOAT fCheckbox254;
	FAUSTFLOAT fCheckbox255;
	FAUSTFLOAT fHslider83;
	double fRec158[2];
	double fVec93[1048576];
	FAUSTFLOAT fHslider84;
	int iRec159[2];
	int iRec160[2];
	double fVec94[262144];
	FAUSTFLOAT fHslider85;
	double fRec162[2];
	double fVec95[2];
	double fRec161[2];
	double fVec96[2];
	double fRec163[2];
	double fVec97[2];
	double fRec164[2];
	double fVec98[2];
	double fRec165[2];
	double fRec16[2];
	FAUSTFLOAT fHslider86;
	double fRec166[2];
	double fConst6;
	double fConst7;
	FAUSTFLOAT fCheckbox256;
	double fRec167[2];
	FAUSTFLOAT fCheckbox257;
	double fRec168[2];
	FAUSTFLOAT fCheckbox258;
	double fRec169[2];
	FAUSTFLOAT fCheckbox259;
	double fRec170[2];
	FAUSTFLOAT fCheckbox260;
	double fRec171[2];
	FAUSTFLOAT fHslider87;
	double fRec172[2];
	FAUSTFLOAT fCheckbox261;
	double fRec173[2];
	FAUSTFLOAT fCheckbox262;
	double fRec174[2];
	FAUSTFLOAT fCheckbox263;
	double fRec175[2];
	FAUSTFLOAT fCheckbox264;
	double fRec176[2];
	FAUSTFLOAT fCheckbox265;
	double fRec177[2];
	FAUSTFLOAT fHslider88;
	double fRec178[2];
	FAUSTFLOAT fCheckbox266;
	double fRec179[2];
	FAUSTFLOAT fCheckbox267;
	double fRec180[2];
	FAUSTFLOAT fCheckbox268;
	double fRec181[2];
	FAUSTFLOAT fCheckbox269;
	double fRec182[2];
	FAUSTFLOAT fCheckbox270;
	double fRec183[2];
	FAUSTFLOAT fHslider89;
	double fRec184[2];
	FAUSTFLOAT fCheckbox271;
	double fRec185[2];
	FAUSTFLOAT fCheckbox272;
	double fRec186[2];
	FAUSTFLOAT fCheckbox273;
	double fRec187[2];
	FAUSTFLOAT fCheckbox274;
	double fRec188[2];
	FAUSTFLOAT fCheckbox275;
	double fRec189[2];
	FAUSTFLOAT fHslider90;
	double fRec190[2];
	FAUSTFLOAT fCheckbox276;
	double fRec191[2];
	FAUSTFLOAT fCheckbox277;
	double fRec192[2];
	FAUSTFLOAT fCheckbox278;
	double fRec193[2];
	FAUSTFLOAT fCheckbox279;
	double fRec194[2];
	FAUSTFLOAT fCheckbox280;
	double fRec195[2];
	FAUSTFLOAT fHslider91;
	double fRec196[2];
	FAUSTFLOAT fCheckbox281;
	double fRec197[2];
	FAUSTFLOAT fCheckbox282;
	double fRec198[2];
	FAUSTFLOAT fCheckbox283;
	double fRec199[2];
	FAUSTFLOAT fCheckbox284;
	double fRec200[2];
	FAUSTFLOAT fCheckbox285;
	double fRec201[2];
	FAUSTFLOAT fHslider92;
	double fRec202[2];
	FAUSTFLOAT fCheckbox286;
	double fRec203[2];
	FAUSTFLOAT fCheckbox287;
	double fRec204[2];
	FAUSTFLOAT fCheckbox288;
	double fRec205[2];
	FAUSTFLOAT fCheckbox289;
	double fRec206[2];
	FAUSTFLOAT fCheckbox290;
	double fRec207[2];
	FAUSTFLOAT fHslider93;
	double fRec208[2];
	FAUSTFLOAT fCheckbox291;
	double fRec209[2];
	FAUSTFLOAT fCheckbox292;
	double fRec210[2];
	FAUSTFLOAT fCheckbox293;
	double fRec211[2];
	FAUSTFLOAT fCheckbox294;
	double fRec212[2];
	FAUSTFLOAT fCheckbox295;
	double fRec213[2];
	FAUSTFLOAT fHslider94;
	double fRec214[2];
	FAUSTFLOAT fCheckbox296;
	double fRec215[2];
	FAUSTFLOAT fCheckbox297;
	double fRec216[2];
	FAUSTFLOAT fCheckbox298;
	double fRec217[2];
	FAUSTFLOAT fCheckbox299;
	double fRec218[2];
	FAUSTFLOAT fCheckbox300;
	double fRec219[2];
	FAUSTFLOAT fHslider95;
	double fRec220[2];
	FAUSTFLOAT fCheckbox301;
	double fRec221[2];
	FAUSTFLOAT fCheckbox302;
	double fRec222[2];
	FAUSTFLOAT fCheckbox303;
	double fRec223[2];
	FAUSTFLOAT fCheckbox304;
	double fRec224[2];
	FAUSTFLOAT fCheckbox305;
	double fRec225[2];
	FAUSTFLOAT fHslider96;
	double fRec226[2];
	FAUSTFLOAT fCheckbox306;
	double fRec227[2];
	FAUSTFLOAT fCheckbox307;
	double fRec228[2];
	FAUSTFLOAT fCheckbox308;
	double fRec229[2];
	FAUSTFLOAT fCheckbox309;
	double fRec230[2];
	FAUSTFLOAT fCheckbox310;
	double fRec231[2];
	FAUSTFLOAT fHslider97;
	double fRec232[2];
	FAUSTFLOAT fCheckbox311;
	double fRec233[2];
	FAUSTFLOAT fCheckbox312;
	double fRec234[2];
	FAUSTFLOAT fCheckbox313;
	double fRec235[2];
	FAUSTFLOAT fCheckbox314;
	double fRec236[2];
	FAUSTFLOAT fCheckbox315;
	double fRec237[2];
	FAUSTFLOAT fHslider98;
	double fRec238[2];
	FAUSTFLOAT fCheckbox316;
	double fRec239[2];
	FAUSTFLOAT fCheckbox317;
	double fRec240[2];
	FAUSTFLOAT fCheckbox318;
	double fRec241[2];
	FAUSTFLOAT fCheckbox319;
	double fRec242[2];
	FAUSTFLOAT fCheckbox320;
	double fRec243[2];
	FAUSTFLOAT fHslider99;
	double fRec244[2];
	FAUSTFLOAT fCheckbox321;
	double fRec245[2];
	FAUSTFLOAT fCheckbox322;
	double fRec246[2];
	FAUSTFLOAT fCheckbox323;
	double fRec247[2];
	FAUSTFLOAT fCheckbox324;
	double fRec248[2];
	FAUSTFLOAT fCheckbox325;
	double fRec249[2];
	FAUSTFLOAT fHslider100;
	double fRec250[2];
	FAUSTFLOAT fCheckbox326;
	double fRec251[2];
	FAUSTFLOAT fCheckbox327;
	double fRec252[2];
	FAUSTFLOAT fCheckbox328;
	double fRec253[2];
	FAUSTFLOAT fCheckbox329;
	double fRec254[2];
	FAUSTFLOAT fCheckbox330;
	double fRec255[2];
	FAUSTFLOAT fHslider101;
	double fRec256[2];
	FAUSTFLOAT fCheckbox331;
	double fRec257[2];
	FAUSTFLOAT fCheckbox332;
	double fRec258[2];
	FAUSTFLOAT fCheckbox333;
	double fRec259[2];
	FAUSTFLOAT fCheckbox334;
	double fRec260[2];
	FAUSTFLOAT fCheckbox335;
	double fRec261[2];
	FAUSTFLOAT fHslider102;
	double fRec262[2];
	FAUSTFLOAT fCheckbox336;
	double fRec263[2];
	FAUSTFLOAT fCheckbox337;
	double fRec264[2];
	FAUSTFLOAT fCheckbox338;
	double fRec265[2];
	FAUSTFLOAT fCheckbox339;
	double fRec266[2];
	FAUSTFLOAT fCheckbox340;
	double fRec267[2];
	FAUSTFLOAT fHslider103;
	FAUSTFLOAT fCheckbox341;
	double fRec268[2];
	FAUSTFLOAT fHslider104;
	double fRec269[2];
	FAUSTFLOAT fEntry0;
	double fRec271[2];
	int iRec272[2];
	FAUSTFLOAT fHslider105;
	int iRec270[2];
	FAUSTFLOAT fHslider106;
	FAUSTFLOAT fHslider107;
	double fRec278[2];
	FAUSTFLOAT fHslider108;
	FAUSTFLOAT fHslider109;
	double fRec279[2];
	FAUSTFLOAT fHslider110;
	FAUSTFLOAT fHslider111;
	double fRec280[2];
	FAUSTFLOAT fCheckbox342;
	double fRec281[2];
	FAUSTFLOAT fCheckbox343;
	double fRec282[2];
	FAUSTFLOAT fCheckbox344;
	double fRec283[2];
	FAUSTFLOAT fCheckbox345;
	double fRec284[2];
	FAUSTFLOAT fCheckbox346;
	double fRec285[2];
	FAUSTFLOAT fCheckbox347;
	double fRec286[2];
	FAUSTFLOAT fCheckbox348;
	double fRec287[2];
	FAUSTFLOAT fCheckbox349;
	double fRec288[2];
	FAUSTFLOAT fCheckbox350;
	double fRec289[2];
	FAUSTFLOAT fCheckbox351;
	double fRec290[2];
	FAUSTFLOAT fCheckbox352;
	double fRec291[2];
	FAUSTFLOAT fCheckbox353;
	double fRec292[2];
	FAUSTFLOAT fCheckbox354;
	double fRec293[2];
	FAUSTFLOAT fCheckbox355;
	double fRec294[2];
	FAUSTFLOAT fCheckbox356;
	double fRec295[2];
	FAUSTFLOAT fCheckbox357;
	double fRec296[2];
	FAUSTFLOAT fHslider112;
	FAUSTFLOAT fHslider113;
	double fRec297[2];
	FAUSTFLOAT fCheckbox358;
	double fRec298[2];
	int iRec299[2];
	FAUSTFLOAT fCheckbox359;
	double fRec300[2];
	FAUSTFLOAT fCheckbox360;
	double fRec301[2];
	FAUSTFLOAT fCheckbox361;
	double fRec302[2];
	FAUSTFLOAT fCheckbox362;
	double fRec303[2];
	FAUSTFLOAT fCheckbox363;
	double fRec304[2];
	FAUSTFLOAT fCheckbox364;
	double fRec305[2];
	FAUSTFLOAT fCheckbox365;
	double fRec306[2];
	FAUSTFLOAT fCheckbox366;
	double fRec307[2];
	FAUSTFLOAT fCheckbox367;
	double fRec308[2];
	FAUSTFLOAT fCheckbox368;
	double fRec309[2];
	FAUSTFLOAT fCheckbox369;
	double fRec310[2];
	FAUSTFLOAT fCheckbox370;
	double fRec311[2];
	FAUSTFLOAT fCheckbox371;
	double fRec312[2];
	FAUSTFLOAT fCheckbox372;
	double fRec313[2];
	FAUSTFLOAT fCheckbox373;
	double fRec314[2];
	FAUSTFLOAT fCheckbox374;
	double fRec315[2];
	FAUSTFLOAT fCheckbox375;
	double fRec316[2];
	int iRec317[2];
	FAUSTFLOAT fCheckbox376;
	double fRec318[2];
	FAUSTFLOAT fCheckbox377;
	double fRec319[2];
	FAUSTFLOAT fCheckbox378;
	double fRec320[2];
	FAUSTFLOAT fCheckbox379;
	double fRec321[2];
	FAUSTFLOAT fCheckbox380;
	double fRec322[2];
	FAUSTFLOAT fCheckbox381;
	double fRec323[2];
	FAUSTFLOAT fCheckbox382;
	double fRec324[2];
	FAUSTFLOAT fCheckbox383;
	double fRec325[2];
	FAUSTFLOAT fCheckbox384;
	double fRec326[2];
	FAUSTFLOAT fCheckbox385;
	double fRec327[2];
	FAUSTFLOAT fCheckbox386;
	double fRec328[2];
	FAUSTFLOAT fCheckbox387;
	double fRec329[2];
	FAUSTFLOAT fCheckbox388;
	double fRec330[2];
	FAUSTFLOAT fCheckbox389;
	double fRec331[2];
	FAUSTFLOAT fCheckbox390;
	double fRec332[2];
	FAUSTFLOAT fCheckbox391;
	double fRec333[2];
	FAUSTFLOAT fCheckbox392;
	double fRec334[2];
	int iRec335[2];
	FAUSTFLOAT fCheckbox393;
	double fRec336[2];
	FAUSTFLOAT fCheckbox394;
	double fRec337[2];
	FAUSTFLOAT fCheckbox395;
	double fRec338[2];
	FAUSTFLOAT fCheckbox396;
	double fRec339[2];
	FAUSTFLOAT fCheckbox397;
	double fRec340[2];
	FAUSTFLOAT fCheckbox398;
	double fRec341[2];
	FAUSTFLOAT fCheckbox399;
	double fRec342[2];
	FAUSTFLOAT fCheckbox400;
	double fRec343[2];
	FAUSTFLOAT fCheckbox401;
	double fRec344[2];
	FAUSTFLOAT fCheckbox402;
	double fRec345[2];
	FAUSTFLOAT fCheckbox403;
	double fRec346[2];
	FAUSTFLOAT fCheckbox404;
	double fRec347[2];
	FAUSTFLOAT fCheckbox405;
	double fRec348[2];
	FAUSTFLOAT fCheckbox406;
	double fRec349[2];
	FAUSTFLOAT fCheckbox407;
	double fRec350[2];
	FAUSTFLOAT fCheckbox408;
	double fRec351[2];
	FAUSTFLOAT fCheckbox409;
	double fRec352[2];
	int iRec353[2];
	FAUSTFLOAT fCheckbox410;
	double fRec354[2];
	FAUSTFLOAT fCheckbox411;
	double fRec355[2];
	FAUSTFLOAT fCheckbox412;
	double fRec356[2];
	FAUSTFLOAT fCheckbox413;
	double fRec357[2];
	FAUSTFLOAT fCheckbox414;
	double fRec358[2];
	FAUSTFLOAT fCheckbox415;
	double fRec359[2];
	FAUSTFLOAT fCheckbox416;
	double fRec360[2];
	FAUSTFLOAT fCheckbox417;
	double fRec361[2];
	FAUSTFLOAT fCheckbox418;
	double fRec362[2];
	FAUSTFLOAT fCheckbox419;
	double fRec363[2];
	FAUSTFLOAT fCheckbox420;
	double fRec364[2];
	FAUSTFLOAT fCheckbox421;
	double fRec365[2];
	FAUSTFLOAT fCheckbox422;
	double fRec366[2];
	FAUSTFLOAT fCheckbox423;
	double fRec367[2];
	FAUSTFLOAT fCheckbox424;
	double fRec368[2];
	FAUSTFLOAT fCheckbox425;
	double fRec369[2];
	FAUSTFLOAT fCheckbox426;
	double fRec370[2];
	int iRec371[2];
	FAUSTFLOAT fCheckbox427;
	double fRec372[2];
	FAUSTFLOAT fCheckbox428;
	double fRec373[2];
	FAUSTFLOAT fCheckbox429;
	double fRec374[2];
	FAUSTFLOAT fCheckbox430;
	double fRec375[2];
	FAUSTFLOAT fCheckbox431;
	double fRec376[2];
	FAUSTFLOAT fCheckbox432;
	double fRec377[2];
	FAUSTFLOAT fCheckbox433;
	double fRec378[2];
	FAUSTFLOAT fCheckbox434;
	double fRec379[2];
	FAUSTFLOAT fCheckbox435;
	double fRec380[2];
	FAUSTFLOAT fCheckbox436;
	double fRec381[2];
	FAUSTFLOAT fCheckbox437;
	double fRec382[2];
	FAUSTFLOAT fCheckbox438;
	double fRec383[2];
	FAUSTFLOAT fCheckbox439;
	double fRec384[2];
	FAUSTFLOAT fCheckbox440;
	double fRec385[2];
	FAUSTFLOAT fCheckbox441;
	double fRec386[2];
	FAUSTFLOAT fCheckbox442;
	double fRec387[2];
	FAUSTFLOAT fHslider114;
	double fRec388[2];
	FAUSTFLOAT fHslider115;
	FAUSTFLOAT fHslider116;
	FAUSTFLOAT fHslider117;
	FAUSTFLOAT fHslider118;
	FAUSTFLOAT fHslider119;
	FAUSTFLOAT fHslider120;
	FAUSTFLOAT fHslider121;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics_lib_name", "Faust Basic Element Library");
		m->declare("basics_lib_version", "0.0");
		m->declare("compilation_options", "-single -scal -I /Users/alainbonardi/Desktop/FilDeSoi1_envoiGrameMars2021 -I /Users/alainbonardi/.FaustLive-CurrentSession-2.0/Libs -I /Users/alainbonardi/.FaustLive-CurrentSession-2.0/Examples");
		m->declare("compile_options", "-lang cpp -es 1 -double -ftz 0");
		m->declare("delays_lib_name", "Faust Delay Library");
		m->declare("delays_lib_version", "0.0");
		m->declare("filename", "FilDeSoi1PanStereo.dsp");
		m->declare("hoa_lib_author", "Pierre Guillot");
		m->declare("hoa_lib_copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m->declare("hoa_lib_name", "High Order Ambisonics library");
		m->declare("library_path", "FilDeSoi1PanStereo");
		m->declare("maths_lib_author", "GRAME");
		m->declare("maths_lib_copyright", "GRAME");
		m->declare("maths_lib_license", "LGPL with exception");
		m->declare("maths_lib_name", "Faust Math Library");
		m->declare("maths_lib_version", "2.0");
		m->declare("name", "FilDeSoi1PanStereo");
		m->declare("noises_lib_name", "Faust Noise Generator Library");
		m->declare("noises_lib_version", "0.0");
		m->declare("oscillators_lib_name", "Faust Oscillator Library");
		m->declare("oscillators_lib_version", "0.0");
		m->declare("routes_lib_name", "Faust Signal Routing Library");
		m->declare("routes_lib_version", "0.0");
		m->declare("signals_lib_name", "Faust Signal Routing Library");
		m->declare("signals_lib_version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
		FilDeSoi1PanStereoSIG0* sig0 = newFilDeSoi1PanStereoSIG0();
		sig0->instanceInitFilDeSoi1PanStereoSIG0(sample_rate);
		sig0->fillFilDeSoi1PanStereoSIG0(65536, ftbl0FilDeSoi1PanStereoSIG0);
		deleteFilDeSoi1PanStereoSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
		fConst1 = (1000.0 / fConst0);
		fConst2 = (30.0 / fConst0);
		fConst3 = (0.001 * fConst0);
		fConst4 = (1.0 / fConst0);
		fConst5 = (0.029999999999999999 * fConst0);
		fConst6 = std::exp((0.0 - (5.0 / fConst0)));
		fConst7 = (1.0 - fConst6);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0);
		fHslider1 = FAUSTFLOAT(20.0);
		fHslider2 = FAUSTFLOAT(1.0);
		fCheckbox0 = FAUSTFLOAT(0.0);
		fHslider3 = FAUSTFLOAT(0.0);
		fCheckbox1 = FAUSTFLOAT(0.0);
		fHslider4 = FAUSTFLOAT(1.0);
		fHslider5 = FAUSTFLOAT(0.0);
		fCheckbox2 = FAUSTFLOAT(0.0);
		fHslider6 = FAUSTFLOAT(1.0);
		fHslider7 = FAUSTFLOAT(0.0);
		fCheckbox3 = FAUSTFLOAT(0.0);
		fHslider8 = FAUSTFLOAT(1.0);
		fHslider9 = FAUSTFLOAT(0.0);
		fCheckbox4 = FAUSTFLOAT(0.0);
		fHslider10 = FAUSTFLOAT(1.0);
		fHslider11 = FAUSTFLOAT(0.0);
		fCheckbox5 = FAUSTFLOAT(0.0);
		fHslider12 = FAUSTFLOAT(1.0);
		fHslider13 = FAUSTFLOAT(0.0);
		fCheckbox6 = FAUSTFLOAT(0.0);
		fHslider14 = FAUSTFLOAT(1.0);
		fHslider15 = FAUSTFLOAT(0.0);
		fCheckbox7 = FAUSTFLOAT(0.0);
		fHslider16 = FAUSTFLOAT(1.0);
		fHslider17 = FAUSTFLOAT(0.0);
		fCheckbox8 = FAUSTFLOAT(0.0);
		fHslider18 = FAUSTFLOAT(1.0);
		fHslider19 = FAUSTFLOAT(0.0);
		fCheckbox9 = FAUSTFLOAT(0.0);
		fHslider20 = FAUSTFLOAT(1.0);
		fHslider21 = FAUSTFLOAT(0.0);
		fCheckbox10 = FAUSTFLOAT(0.0);
		fHslider22 = FAUSTFLOAT(1.0);
		fHslider23 = FAUSTFLOAT(0.0);
		fCheckbox11 = FAUSTFLOAT(0.0);
		fHslider24 = FAUSTFLOAT(1.0);
		fHslider25 = FAUSTFLOAT(0.0);
		fCheckbox12 = FAUSTFLOAT(0.0);
		fHslider26 = FAUSTFLOAT(1.0);
		fHslider27 = FAUSTFLOAT(0.0);
		fCheckbox13 = FAUSTFLOAT(0.0);
		fHslider28 = FAUSTFLOAT(1.0);
		fHslider29 = FAUSTFLOAT(0.0);
		fCheckbox14 = FAUSTFLOAT(0.0);
		fHslider30 = FAUSTFLOAT(1.0);
		fHslider31 = FAUSTFLOAT(0.0);
		fCheckbox15 = FAUSTFLOAT(0.0);
		fHslider32 = FAUSTFLOAT(1.0);
		fHslider33 = FAUSTFLOAT(0.0);
		fHslider34 = FAUSTFLOAT(1.0);
		fHslider35 = FAUSTFLOAT(0.0);
		fHslider36 = FAUSTFLOAT(1.0);
		fHslider37 = FAUSTFLOAT(100.0);
		fHslider38 = FAUSTFLOAT(1.0);
		fHslider39 = FAUSTFLOAT(0.0);
		fHslider40 = FAUSTFLOAT(64.0);
		fCheckbox16 = FAUSTFLOAT(0.0);
		fCheckbox17 = FAUSTFLOAT(0.0);
		fCheckbox18 = FAUSTFLOAT(0.0);
		fCheckbox19 = FAUSTFLOAT(0.0);
		fCheckbox20 = FAUSTFLOAT(0.0);
		fCheckbox21 = FAUSTFLOAT(0.0);
		fCheckbox22 = FAUSTFLOAT(0.0);
		fCheckbox23 = FAUSTFLOAT(0.0);
		fCheckbox24 = FAUSTFLOAT(0.0);
		fCheckbox25 = FAUSTFLOAT(0.0);
		fCheckbox26 = FAUSTFLOAT(0.0);
		fCheckbox27 = FAUSTFLOAT(0.0);
		fCheckbox28 = FAUSTFLOAT(0.0);
		fCheckbox29 = FAUSTFLOAT(0.0);
		fCheckbox30 = FAUSTFLOAT(0.0);
		fCheckbox31 = FAUSTFLOAT(0.0);
		fHslider41 = FAUSTFLOAT(1.0);
		fHslider42 = FAUSTFLOAT(200.0);
		fHslider43 = FAUSTFLOAT(0.0);
		fCheckbox32 = FAUSTFLOAT(0.0);
		fCheckbox33 = FAUSTFLOAT(0.0);
		fCheckbox34 = FAUSTFLOAT(0.0);
		fCheckbox35 = FAUSTFLOAT(0.0);
		fCheckbox36 = FAUSTFLOAT(0.0);
		fCheckbox37 = FAUSTFLOAT(0.0);
		fCheckbox38 = FAUSTFLOAT(0.0);
		fCheckbox39 = FAUSTFLOAT(0.0);
		fCheckbox40 = FAUSTFLOAT(0.0);
		fCheckbox41 = FAUSTFLOAT(0.0);
		fCheckbox42 = FAUSTFLOAT(0.0);
		fCheckbox43 = FAUSTFLOAT(0.0);
		fCheckbox44 = FAUSTFLOAT(0.0);
		fCheckbox45 = FAUSTFLOAT(0.0);
		fCheckbox46 = FAUSTFLOAT(0.0);
		fCheckbox47 = FAUSTFLOAT(0.0);
		fHslider44 = FAUSTFLOAT(1.0);
		fHslider45 = FAUSTFLOAT(300.0);
		fHslider46 = FAUSTFLOAT(0.0);
		fCheckbox48 = FAUSTFLOAT(0.0);
		fCheckbox49 = FAUSTFLOAT(0.0);
		fCheckbox50 = FAUSTFLOAT(0.0);
		fCheckbox51 = FAUSTFLOAT(0.0);
		fCheckbox52 = FAUSTFLOAT(0.0);
		fCheckbox53 = FAUSTFLOAT(0.0);
		fCheckbox54 = FAUSTFLOAT(0.0);
		fCheckbox55 = FAUSTFLOAT(0.0);
		fCheckbox56 = FAUSTFLOAT(0.0);
		fCheckbox57 = FAUSTFLOAT(0.0);
		fCheckbox58 = FAUSTFLOAT(0.0);
		fCheckbox59 = FAUSTFLOAT(0.0);
		fCheckbox60 = FAUSTFLOAT(0.0);
		fCheckbox61 = FAUSTFLOAT(0.0);
		fCheckbox62 = FAUSTFLOAT(0.0);
		fCheckbox63 = FAUSTFLOAT(0.0);
		fHslider47 = FAUSTFLOAT(1.0);
		fHslider48 = FAUSTFLOAT(400.0);
		fHslider49 = FAUSTFLOAT(0.0);
		fCheckbox64 = FAUSTFLOAT(0.0);
		fCheckbox65 = FAUSTFLOAT(0.0);
		fCheckbox66 = FAUSTFLOAT(0.0);
		fCheckbox67 = FAUSTFLOAT(0.0);
		fCheckbox68 = FAUSTFLOAT(0.0);
		fCheckbox69 = FAUSTFLOAT(0.0);
		fCheckbox70 = FAUSTFLOAT(0.0);
		fCheckbox71 = FAUSTFLOAT(0.0);
		fCheckbox72 = FAUSTFLOAT(0.0);
		fCheckbox73 = FAUSTFLOAT(0.0);
		fCheckbox74 = FAUSTFLOAT(0.0);
		fCheckbox75 = FAUSTFLOAT(0.0);
		fCheckbox76 = FAUSTFLOAT(0.0);
		fCheckbox77 = FAUSTFLOAT(0.0);
		fCheckbox78 = FAUSTFLOAT(0.0);
		fCheckbox79 = FAUSTFLOAT(0.0);
		fHslider50 = FAUSTFLOAT(1.0);
		fHslider51 = FAUSTFLOAT(500.0);
		fHslider52 = FAUSTFLOAT(0.0);
		fCheckbox80 = FAUSTFLOAT(0.0);
		fCheckbox81 = FAUSTFLOAT(0.0);
		fCheckbox82 = FAUSTFLOAT(0.0);
		fCheckbox83 = FAUSTFLOAT(0.0);
		fCheckbox84 = FAUSTFLOAT(0.0);
		fCheckbox85 = FAUSTFLOAT(0.0);
		fCheckbox86 = FAUSTFLOAT(0.0);
		fCheckbox87 = FAUSTFLOAT(0.0);
		fCheckbox88 = FAUSTFLOAT(0.0);
		fCheckbox89 = FAUSTFLOAT(0.0);
		fCheckbox90 = FAUSTFLOAT(0.0);
		fCheckbox91 = FAUSTFLOAT(0.0);
		fCheckbox92 = FAUSTFLOAT(0.0);
		fCheckbox93 = FAUSTFLOAT(0.0);
		fCheckbox94 = FAUSTFLOAT(0.0);
		fCheckbox95 = FAUSTFLOAT(0.0);
		fHslider53 = FAUSTFLOAT(1.0);
		fHslider54 = FAUSTFLOAT(600.0);
		fHslider55 = FAUSTFLOAT(0.0);
		fCheckbox96 = FAUSTFLOAT(0.0);
		fCheckbox97 = FAUSTFLOAT(0.0);
		fCheckbox98 = FAUSTFLOAT(0.0);
		fCheckbox99 = FAUSTFLOAT(0.0);
		fCheckbox100 = FAUSTFLOAT(0.0);
		fCheckbox101 = FAUSTFLOAT(0.0);
		fCheckbox102 = FAUSTFLOAT(0.0);
		fCheckbox103 = FAUSTFLOAT(0.0);
		fCheckbox104 = FAUSTFLOAT(0.0);
		fCheckbox105 = FAUSTFLOAT(0.0);
		fCheckbox106 = FAUSTFLOAT(0.0);
		fCheckbox107 = FAUSTFLOAT(0.0);
		fCheckbox108 = FAUSTFLOAT(0.0);
		fCheckbox109 = FAUSTFLOAT(0.0);
		fCheckbox110 = FAUSTFLOAT(0.0);
		fCheckbox111 = FAUSTFLOAT(0.0);
		fHslider56 = FAUSTFLOAT(1.0);
		fHslider57 = FAUSTFLOAT(700.0);
		fHslider58 = FAUSTFLOAT(0.0);
		fCheckbox112 = FAUSTFLOAT(0.0);
		fCheckbox113 = FAUSTFLOAT(0.0);
		fCheckbox114 = FAUSTFLOAT(0.0);
		fCheckbox115 = FAUSTFLOAT(0.0);
		fCheckbox116 = FAUSTFLOAT(0.0);
		fCheckbox117 = FAUSTFLOAT(0.0);
		fCheckbox118 = FAUSTFLOAT(0.0);
		fCheckbox119 = FAUSTFLOAT(0.0);
		fCheckbox120 = FAUSTFLOAT(0.0);
		fCheckbox121 = FAUSTFLOAT(0.0);
		fCheckbox122 = FAUSTFLOAT(0.0);
		fCheckbox123 = FAUSTFLOAT(0.0);
		fCheckbox124 = FAUSTFLOAT(0.0);
		fCheckbox125 = FAUSTFLOAT(0.0);
		fCheckbox126 = FAUSTFLOAT(0.0);
		fCheckbox127 = FAUSTFLOAT(0.0);
		fHslider59 = FAUSTFLOAT(1.0);
		fHslider60 = FAUSTFLOAT(800.0);
		fHslider61 = FAUSTFLOAT(0.0);
		fCheckbox128 = FAUSTFLOAT(0.0);
		fCheckbox129 = FAUSTFLOAT(0.0);
		fCheckbox130 = FAUSTFLOAT(0.0);
		fCheckbox131 = FAUSTFLOAT(0.0);
		fCheckbox132 = FAUSTFLOAT(0.0);
		fCheckbox133 = FAUSTFLOAT(0.0);
		fCheckbox134 = FAUSTFLOAT(0.0);
		fCheckbox135 = FAUSTFLOAT(0.0);
		fCheckbox136 = FAUSTFLOAT(0.0);
		fCheckbox137 = FAUSTFLOAT(0.0);
		fCheckbox138 = FAUSTFLOAT(0.0);
		fCheckbox139 = FAUSTFLOAT(0.0);
		fCheckbox140 = FAUSTFLOAT(0.0);
		fCheckbox141 = FAUSTFLOAT(0.0);
		fCheckbox142 = FAUSTFLOAT(0.0);
		fCheckbox143 = FAUSTFLOAT(0.0);
		fHslider62 = FAUSTFLOAT(1.0);
		fHslider63 = FAUSTFLOAT(900.0);
		fHslider64 = FAUSTFLOAT(0.0);
		fCheckbox144 = FAUSTFLOAT(0.0);
		fCheckbox145 = FAUSTFLOAT(0.0);
		fCheckbox146 = FAUSTFLOAT(0.0);
		fCheckbox147 = FAUSTFLOAT(0.0);
		fCheckbox148 = FAUSTFLOAT(0.0);
		fCheckbox149 = FAUSTFLOAT(0.0);
		fCheckbox150 = FAUSTFLOAT(0.0);
		fCheckbox151 = FAUSTFLOAT(0.0);
		fCheckbox152 = FAUSTFLOAT(0.0);
		fCheckbox153 = FAUSTFLOAT(0.0);
		fCheckbox154 = FAUSTFLOAT(0.0);
		fCheckbox155 = FAUSTFLOAT(0.0);
		fCheckbox156 = FAUSTFLOAT(0.0);
		fCheckbox157 = FAUSTFLOAT(0.0);
		fCheckbox158 = FAUSTFLOAT(0.0);
		fCheckbox159 = FAUSTFLOAT(0.0);
		fHslider65 = FAUSTFLOAT(1.0);
		fHslider66 = FAUSTFLOAT(1000.0);
		fHslider67 = FAUSTFLOAT(0.0);
		fCheckbox160 = FAUSTFLOAT(0.0);
		fCheckbox161 = FAUSTFLOAT(0.0);
		fCheckbox162 = FAUSTFLOAT(0.0);
		fCheckbox163 = FAUSTFLOAT(0.0);
		fCheckbox164 = FAUSTFLOAT(0.0);
		fCheckbox165 = FAUSTFLOAT(0.0);
		fCheckbox166 = FAUSTFLOAT(0.0);
		fCheckbox167 = FAUSTFLOAT(0.0);
		fCheckbox168 = FAUSTFLOAT(0.0);
		fCheckbox169 = FAUSTFLOAT(0.0);
		fCheckbox170 = FAUSTFLOAT(0.0);
		fCheckbox171 = FAUSTFLOAT(0.0);
		fCheckbox172 = FAUSTFLOAT(0.0);
		fCheckbox173 = FAUSTFLOAT(0.0);
		fCheckbox174 = FAUSTFLOAT(0.0);
		fCheckbox175 = FAUSTFLOAT(0.0);
		fHslider68 = FAUSTFLOAT(1.0);
		fHslider69 = FAUSTFLOAT(1100.0);
		fHslider70 = FAUSTFLOAT(0.0);
		fCheckbox176 = FAUSTFLOAT(0.0);
		fCheckbox177 = FAUSTFLOAT(0.0);
		fCheckbox178 = FAUSTFLOAT(0.0);
		fCheckbox179 = FAUSTFLOAT(0.0);
		fCheckbox180 = FAUSTFLOAT(0.0);
		fCheckbox181 = FAUSTFLOAT(0.0);
		fCheckbox182 = FAUSTFLOAT(0.0);
		fCheckbox183 = FAUSTFLOAT(0.0);
		fCheckbox184 = FAUSTFLOAT(0.0);
		fCheckbox185 = FAUSTFLOAT(0.0);
		fCheckbox186 = FAUSTFLOAT(0.0);
		fCheckbox187 = FAUSTFLOAT(0.0);
		fCheckbox188 = FAUSTFLOAT(0.0);
		fCheckbox189 = FAUSTFLOAT(0.0);
		fCheckbox190 = FAUSTFLOAT(0.0);
		fCheckbox191 = FAUSTFLOAT(0.0);
		fHslider71 = FAUSTFLOAT(1.0);
		fHslider72 = FAUSTFLOAT(1200.0);
		fHslider73 = FAUSTFLOAT(0.0);
		fCheckbox192 = FAUSTFLOAT(0.0);
		fCheckbox193 = FAUSTFLOAT(0.0);
		fCheckbox194 = FAUSTFLOAT(0.0);
		fCheckbox195 = FAUSTFLOAT(0.0);
		fCheckbox196 = FAUSTFLOAT(0.0);
		fCheckbox197 = FAUSTFLOAT(0.0);
		fCheckbox198 = FAUSTFLOAT(0.0);
		fCheckbox199 = FAUSTFLOAT(0.0);
		fCheckbox200 = FAUSTFLOAT(0.0);
		fCheckbox201 = FAUSTFLOAT(0.0);
		fCheckbox202 = FAUSTFLOAT(0.0);
		fCheckbox203 = FAUSTFLOAT(0.0);
		fCheckbox204 = FAUSTFLOAT(0.0);
		fCheckbox205 = FAUSTFLOAT(0.0);
		fCheckbox206 = FAUSTFLOAT(0.0);
		fCheckbox207 = FAUSTFLOAT(0.0);
		fHslider74 = FAUSTFLOAT(1.0);
		fHslider75 = FAUSTFLOAT(1300.0);
		fHslider76 = FAUSTFLOAT(0.0);
		fCheckbox208 = FAUSTFLOAT(0.0);
		fCheckbox209 = FAUSTFLOAT(0.0);
		fCheckbox210 = FAUSTFLOAT(0.0);
		fCheckbox211 = FAUSTFLOAT(0.0);
		fCheckbox212 = FAUSTFLOAT(0.0);
		fCheckbox213 = FAUSTFLOAT(0.0);
		fCheckbox214 = FAUSTFLOAT(0.0);
		fCheckbox215 = FAUSTFLOAT(0.0);
		fCheckbox216 = FAUSTFLOAT(0.0);
		fCheckbox217 = FAUSTFLOAT(0.0);
		fCheckbox218 = FAUSTFLOAT(0.0);
		fCheckbox219 = FAUSTFLOAT(0.0);
		fCheckbox220 = FAUSTFLOAT(0.0);
		fCheckbox221 = FAUSTFLOAT(0.0);
		fCheckbox222 = FAUSTFLOAT(0.0);
		fCheckbox223 = FAUSTFLOAT(0.0);
		fHslider77 = FAUSTFLOAT(1.0);
		fHslider78 = FAUSTFLOAT(1400.0);
		fHslider79 = FAUSTFLOAT(0.0);
		fCheckbox224 = FAUSTFLOAT(0.0);
		fCheckbox225 = FAUSTFLOAT(0.0);
		fCheckbox226 = FAUSTFLOAT(0.0);
		fCheckbox227 = FAUSTFLOAT(0.0);
		fCheckbox228 = FAUSTFLOAT(0.0);
		fCheckbox229 = FAUSTFLOAT(0.0);
		fCheckbox230 = FAUSTFLOAT(0.0);
		fCheckbox231 = FAUSTFLOAT(0.0);
		fCheckbox232 = FAUSTFLOAT(0.0);
		fCheckbox233 = FAUSTFLOAT(0.0);
		fCheckbox234 = FAUSTFLOAT(0.0);
		fCheckbox235 = FAUSTFLOAT(0.0);
		fCheckbox236 = FAUSTFLOAT(0.0);
		fCheckbox237 = FAUSTFLOAT(0.0);
		fCheckbox238 = FAUSTFLOAT(0.0);
		fCheckbox239 = FAUSTFLOAT(0.0);
		fHslider80 = FAUSTFLOAT(1.0);
		fHslider81 = FAUSTFLOAT(1500.0);
		fHslider82 = FAUSTFLOAT(0.0);
		fCheckbox240 = FAUSTFLOAT(0.0);
		fCheckbox241 = FAUSTFLOAT(0.0);
		fCheckbox242 = FAUSTFLOAT(0.0);
		fCheckbox243 = FAUSTFLOAT(0.0);
		fCheckbox244 = FAUSTFLOAT(0.0);
		fCheckbox245 = FAUSTFLOAT(0.0);
		fCheckbox246 = FAUSTFLOAT(0.0);
		fCheckbox247 = FAUSTFLOAT(0.0);
		fCheckbox248 = FAUSTFLOAT(0.0);
		fCheckbox249 = FAUSTFLOAT(0.0);
		fCheckbox250 = FAUSTFLOAT(0.0);
		fCheckbox251 = FAUSTFLOAT(0.0);
		fCheckbox252 = FAUSTFLOAT(0.0);
		fCheckbox253 = FAUSTFLOAT(0.0);
		fCheckbox254 = FAUSTFLOAT(0.0);
		fCheckbox255 = FAUSTFLOAT(0.0);
		fHslider83 = FAUSTFLOAT(1.0);
		fHslider84 = FAUSTFLOAT(1600.0);
		fHslider85 = FAUSTFLOAT(0.0);
		fHslider86 = FAUSTFLOAT(1.0);
		fCheckbox256 = FAUSTFLOAT(0.0);
		fCheckbox257 = FAUSTFLOAT(0.0);
		fCheckbox258 = FAUSTFLOAT(0.0);
		fCheckbox259 = FAUSTFLOAT(0.0);
		fCheckbox260 = FAUSTFLOAT(0.0);
		fHslider87 = FAUSTFLOAT(1.0);
		fCheckbox261 = FAUSTFLOAT(0.0);
		fCheckbox262 = FAUSTFLOAT(0.0);
		fCheckbox263 = FAUSTFLOAT(0.0);
		fCheckbox264 = FAUSTFLOAT(0.0);
		fCheckbox265 = FAUSTFLOAT(0.0);
		fHslider88 = FAUSTFLOAT(1.0);
		fCheckbox266 = FAUSTFLOAT(0.0);
		fCheckbox267 = FAUSTFLOAT(0.0);
		fCheckbox268 = FAUSTFLOAT(0.0);
		fCheckbox269 = FAUSTFLOAT(0.0);
		fCheckbox270 = FAUSTFLOAT(0.0);
		fHslider89 = FAUSTFLOAT(1.0);
		fCheckbox271 = FAUSTFLOAT(0.0);
		fCheckbox272 = FAUSTFLOAT(0.0);
		fCheckbox273 = FAUSTFLOAT(0.0);
		fCheckbox274 = FAUSTFLOAT(0.0);
		fCheckbox275 = FAUSTFLOAT(0.0);
		fHslider90 = FAUSTFLOAT(1.0);
		fCheckbox276 = FAUSTFLOAT(0.0);
		fCheckbox277 = FAUSTFLOAT(0.0);
		fCheckbox278 = FAUSTFLOAT(0.0);
		fCheckbox279 = FAUSTFLOAT(0.0);
		fCheckbox280 = FAUSTFLOAT(0.0);
		fHslider91 = FAUSTFLOAT(1.0);
		fCheckbox281 = FAUSTFLOAT(0.0);
		fCheckbox282 = FAUSTFLOAT(0.0);
		fCheckbox283 = FAUSTFLOAT(0.0);
		fCheckbox284 = FAUSTFLOAT(0.0);
		fCheckbox285 = FAUSTFLOAT(0.0);
		fHslider92 = FAUSTFLOAT(1.0);
		fCheckbox286 = FAUSTFLOAT(0.0);
		fCheckbox287 = FAUSTFLOAT(0.0);
		fCheckbox288 = FAUSTFLOAT(0.0);
		fCheckbox289 = FAUSTFLOAT(0.0);
		fCheckbox290 = FAUSTFLOAT(0.0);
		fHslider93 = FAUSTFLOAT(1.0);
		fCheckbox291 = FAUSTFLOAT(0.0);
		fCheckbox292 = FAUSTFLOAT(0.0);
		fCheckbox293 = FAUSTFLOAT(0.0);
		fCheckbox294 = FAUSTFLOAT(0.0);
		fCheckbox295 = FAUSTFLOAT(0.0);
		fHslider94 = FAUSTFLOAT(1.0);
		fCheckbox296 = FAUSTFLOAT(0.0);
		fCheckbox297 = FAUSTFLOAT(0.0);
		fCheckbox298 = FAUSTFLOAT(0.0);
		fCheckbox299 = FAUSTFLOAT(0.0);
		fCheckbox300 = FAUSTFLOAT(0.0);
		fHslider95 = FAUSTFLOAT(1.0);
		fCheckbox301 = FAUSTFLOAT(0.0);
		fCheckbox302 = FAUSTFLOAT(0.0);
		fCheckbox303 = FAUSTFLOAT(0.0);
		fCheckbox304 = FAUSTFLOAT(0.0);
		fCheckbox305 = FAUSTFLOAT(0.0);
		fHslider96 = FAUSTFLOAT(1.0);
		fCheckbox306 = FAUSTFLOAT(0.0);
		fCheckbox307 = FAUSTFLOAT(0.0);
		fCheckbox308 = FAUSTFLOAT(0.0);
		fCheckbox309 = FAUSTFLOAT(0.0);
		fCheckbox310 = FAUSTFLOAT(0.0);
		fHslider97 = FAUSTFLOAT(1.0);
		fCheckbox311 = FAUSTFLOAT(0.0);
		fCheckbox312 = FAUSTFLOAT(0.0);
		fCheckbox313 = FAUSTFLOAT(0.0);
		fCheckbox314 = FAUSTFLOAT(0.0);
		fCheckbox315 = FAUSTFLOAT(0.0);
		fHslider98 = FAUSTFLOAT(1.0);
		fCheckbox316 = FAUSTFLOAT(0.0);
		fCheckbox317 = FAUSTFLOAT(0.0);
		fCheckbox318 = FAUSTFLOAT(0.0);
		fCheckbox319 = FAUSTFLOAT(0.0);
		fCheckbox320 = FAUSTFLOAT(0.0);
		fHslider99 = FAUSTFLOAT(1.0);
		fCheckbox321 = FAUSTFLOAT(0.0);
		fCheckbox322 = FAUSTFLOAT(0.0);
		fCheckbox323 = FAUSTFLOAT(0.0);
		fCheckbox324 = FAUSTFLOAT(0.0);
		fCheckbox325 = FAUSTFLOAT(0.0);
		fHslider100 = FAUSTFLOAT(1.0);
		fCheckbox326 = FAUSTFLOAT(0.0);
		fCheckbox327 = FAUSTFLOAT(0.0);
		fCheckbox328 = FAUSTFLOAT(0.0);
		fCheckbox329 = FAUSTFLOAT(0.0);
		fCheckbox330 = FAUSTFLOAT(0.0);
		fHslider101 = FAUSTFLOAT(-34.0);
		fCheckbox331 = FAUSTFLOAT(0.0);
		fCheckbox332 = FAUSTFLOAT(0.0);
		fCheckbox333 = FAUSTFLOAT(0.0);
		fCheckbox334 = FAUSTFLOAT(0.0);
		fCheckbox335 = FAUSTFLOAT(0.0);
		fHslider102 = FAUSTFLOAT(1.0);
		fCheckbox336 = FAUSTFLOAT(0.0);
		fCheckbox337 = FAUSTFLOAT(0.0);
		fCheckbox338 = FAUSTFLOAT(0.0);
		fCheckbox339 = FAUSTFLOAT(0.0);
		fCheckbox340 = FAUSTFLOAT(0.0);
		fHslider103 = FAUSTFLOAT(0.0);
		fCheckbox341 = FAUSTFLOAT(0.0);
		fHslider104 = FAUSTFLOAT(0.0);
		fEntry0 = FAUSTFLOAT(10.0);
		fHslider105 = FAUSTFLOAT(0.5);
		fHslider106 = FAUSTFLOAT(0.0);
		fHslider107 = FAUSTFLOAT(0.10000000000000001);
		fHslider108 = FAUSTFLOAT(0.0);
		fHslider109 = FAUSTFLOAT(0.10000000000000001);
		fHslider110 = FAUSTFLOAT(0.0);
		fHslider111 = FAUSTFLOAT(0.10000000000000001);
		fCheckbox342 = FAUSTFLOAT(0.0);
		fCheckbox343 = FAUSTFLOAT(0.0);
		fCheckbox344 = FAUSTFLOAT(0.0);
		fCheckbox345 = FAUSTFLOAT(0.0);
		fCheckbox346 = FAUSTFLOAT(0.0);
		fCheckbox347 = FAUSTFLOAT(0.0);
		fCheckbox348 = FAUSTFLOAT(0.0);
		fCheckbox349 = FAUSTFLOAT(0.0);
		fCheckbox350 = FAUSTFLOAT(0.0);
		fCheckbox351 = FAUSTFLOAT(0.0);
		fCheckbox352 = FAUSTFLOAT(0.0);
		fCheckbox353 = FAUSTFLOAT(0.0);
		fCheckbox354 = FAUSTFLOAT(0.0);
		fCheckbox355 = FAUSTFLOAT(0.0);
		fCheckbox356 = FAUSTFLOAT(0.0);
		fCheckbox357 = FAUSTFLOAT(0.0);
		fHslider112 = FAUSTFLOAT(0.0);
		fHslider113 = FAUSTFLOAT(0.10000000000000001);
		fCheckbox358 = FAUSTFLOAT(0.0);
		fCheckbox359 = FAUSTFLOAT(0.0);
		fCheckbox360 = FAUSTFLOAT(0.0);
		fCheckbox361 = FAUSTFLOAT(0.0);
		fCheckbox362 = FAUSTFLOAT(0.0);
		fCheckbox363 = FAUSTFLOAT(0.0);
		fCheckbox364 = FAUSTFLOAT(0.0);
		fCheckbox365 = FAUSTFLOAT(0.0);
		fCheckbox366 = FAUSTFLOAT(0.0);
		fCheckbox367 = FAUSTFLOAT(0.0);
		fCheckbox368 = FAUSTFLOAT(0.0);
		fCheckbox369 = FAUSTFLOAT(0.0);
		fCheckbox370 = FAUSTFLOAT(0.0);
		fCheckbox371 = FAUSTFLOAT(0.0);
		fCheckbox372 = FAUSTFLOAT(0.0);
		fCheckbox373 = FAUSTFLOAT(0.0);
		fCheckbox374 = FAUSTFLOAT(0.0);
		fCheckbox375 = FAUSTFLOAT(0.0);
		fCheckbox376 = FAUSTFLOAT(0.0);
		fCheckbox377 = FAUSTFLOAT(0.0);
		fCheckbox378 = FAUSTFLOAT(0.0);
		fCheckbox379 = FAUSTFLOAT(0.0);
		fCheckbox380 = FAUSTFLOAT(0.0);
		fCheckbox381 = FAUSTFLOAT(0.0);
		fCheckbox382 = FAUSTFLOAT(0.0);
		fCheckbox383 = FAUSTFLOAT(0.0);
		fCheckbox384 = FAUSTFLOAT(0.0);
		fCheckbox385 = FAUSTFLOAT(0.0);
		fCheckbox386 = FAUSTFLOAT(0.0);
		fCheckbox387 = FAUSTFLOAT(0.0);
		fCheckbox388 = FAUSTFLOAT(0.0);
		fCheckbox389 = FAUSTFLOAT(0.0);
		fCheckbox390 = FAUSTFLOAT(0.0);
		fCheckbox391 = FAUSTFLOAT(0.0);
		fCheckbox392 = FAUSTFLOAT(0.0);
		fCheckbox393 = FAUSTFLOAT(0.0);
		fCheckbox394 = FAUSTFLOAT(0.0);
		fCheckbox395 = FAUSTFLOAT(0.0);
		fCheckbox396 = FAUSTFLOAT(0.0);
		fCheckbox397 = FAUSTFLOAT(0.0);
		fCheckbox398 = FAUSTFLOAT(0.0);
		fCheckbox399 = FAUSTFLOAT(0.0);
		fCheckbox400 = FAUSTFLOAT(0.0);
		fCheckbox401 = FAUSTFLOAT(0.0);
		fCheckbox402 = FAUSTFLOAT(0.0);
		fCheckbox403 = FAUSTFLOAT(0.0);
		fCheckbox404 = FAUSTFLOAT(0.0);
		fCheckbox405 = FAUSTFLOAT(0.0);
		fCheckbox406 = FAUSTFLOAT(0.0);
		fCheckbox407 = FAUSTFLOAT(0.0);
		fCheckbox408 = FAUSTFLOAT(0.0);
		fCheckbox409 = FAUSTFLOAT(0.0);
		fCheckbox410 = FAUSTFLOAT(0.0);
		fCheckbox411 = FAUSTFLOAT(0.0);
		fCheckbox412 = FAUSTFLOAT(0.0);
		fCheckbox413 = FAUSTFLOAT(0.0);
		fCheckbox414 = FAUSTFLOAT(0.0);
		fCheckbox415 = FAUSTFLOAT(0.0);
		fCheckbox416 = FAUSTFLOAT(0.0);
		fCheckbox417 = FAUSTFLOAT(0.0);
		fCheckbox418 = FAUSTFLOAT(0.0);
		fCheckbox419 = FAUSTFLOAT(0.0);
		fCheckbox420 = FAUSTFLOAT(0.0);
		fCheckbox421 = FAUSTFLOAT(0.0);
		fCheckbox422 = FAUSTFLOAT(0.0);
		fCheckbox423 = FAUSTFLOAT(0.0);
		fCheckbox424 = FAUSTFLOAT(0.0);
		fCheckbox425 = FAUSTFLOAT(0.0);
		fCheckbox426 = FAUSTFLOAT(0.0);
		fCheckbox427 = FAUSTFLOAT(0.0);
		fCheckbox428 = FAUSTFLOAT(0.0);
		fCheckbox429 = FAUSTFLOAT(0.0);
		fCheckbox430 = FAUSTFLOAT(0.0);
		fCheckbox431 = FAUSTFLOAT(0.0);
		fCheckbox432 = FAUSTFLOAT(0.0);
		fCheckbox433 = FAUSTFLOAT(0.0);
		fCheckbox434 = FAUSTFLOAT(0.0);
		fCheckbox435 = FAUSTFLOAT(0.0);
		fCheckbox436 = FAUSTFLOAT(0.0);
		fCheckbox437 = FAUSTFLOAT(0.0);
		fCheckbox438 = FAUSTFLOAT(0.0);
		fCheckbox439 = FAUSTFLOAT(0.0);
		fCheckbox440 = FAUSTFLOAT(0.0);
		fCheckbox441 = FAUSTFLOAT(0.0);
		fCheckbox442 = FAUSTFLOAT(0.0);
		fHslider114 = FAUSTFLOAT(30.0);
		fHslider115 = FAUSTFLOAT(45.0);
		fHslider116 = FAUSTFLOAT(90.0);
		fHslider117 = FAUSTFLOAT(135.0);
		fHslider118 = FAUSTFLOAT(180.0);
		fHslider119 = FAUSTFLOAT(225.0);
		fHslider120 = FAUSTFLOAT(270.0);
		fHslider121 = FAUSTFLOAT(315.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec18[l2] = 0.0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec19[l4] = 0.0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec20[l5] = 0.0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec21[l6] = 0.0;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec22[l7] = 0.0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec23[l8] = 0.0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec24[l9] = 0.0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec25[l10] = 0.0;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec26[l11] = 0.0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec27[l12] = 0.0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec28[l13] = 0.0;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec29[l14] = 0.0;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec30[l15] = 0.0;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec31[l16] = 0.0;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec32[l17] = 0.0;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec33[l18] = 0.0;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec34[l19] = 0.0;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec35[l20] = 0.0;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec36[l21] = 0.0;
		}
		IOTA = 0;
		for (int l22 = 0; (l22 < 1048576); l22 = (l22 + 1)) {
			fVec1[l22] = 0.0;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			iRec37[l23] = 0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec2[l24] = 0.0;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			iRec38[l25] = 0;
		}
		for (int l26 = 0; (l26 < 262144); l26 = (l26 + 1)) {
			fVec3[l26] = 0.0;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec4[l27] = 0.0;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec41[l28] = 0.0;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec42[l29] = 0.0;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec40[l30] = 0.0;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec5[l31] = 0.0;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec39[l32] = 0.0;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec6[l33] = 0.0;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec43[l34] = 0.0;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec7[l35] = 0.0;
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec44[l36] = 0.0;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec8[l37] = 0.0;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec45[l38] = 0.0;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec1[l39] = 0.0;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec46[l40] = 0.0;
		}
		for (int l41 = 0; (l41 < 1048576); l41 = (l41 + 1)) {
			fVec9[l41] = 0.0;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			iRec47[l42] = 0;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			iRec48[l43] = 0;
		}
		for (int l44 = 0; (l44 < 262144); l44 = (l44 + 1)) {
			fVec10[l44] = 0.0;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec50[l45] = 0.0;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec11[l46] = 0.0;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec49[l47] = 0.0;
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec12[l48] = 0.0;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec51[l49] = 0.0;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec13[l50] = 0.0;
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec52[l51] = 0.0;
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec14[l52] = 0.0;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec53[l53] = 0.0;
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec2[l54] = 0.0;
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec54[l55] = 0.0;
		}
		for (int l56 = 0; (l56 < 1048576); l56 = (l56 + 1)) {
			fVec15[l56] = 0.0;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			iRec55[l57] = 0;
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			iRec56[l58] = 0;
		}
		for (int l59 = 0; (l59 < 262144); l59 = (l59 + 1)) {
			fVec16[l59] = 0.0;
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec58[l60] = 0.0;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec17[l61] = 0.0;
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec57[l62] = 0.0;
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fVec18[l63] = 0.0;
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec59[l64] = 0.0;
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fVec19[l65] = 0.0;
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec60[l66] = 0.0;
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fVec20[l67] = 0.0;
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec61[l68] = 0.0;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec3[l69] = 0.0;
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec62[l70] = 0.0;
		}
		for (int l71 = 0; (l71 < 1048576); l71 = (l71 + 1)) {
			fVec21[l71] = 0.0;
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			iRec63[l72] = 0;
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			iRec64[l73] = 0;
		}
		for (int l74 = 0; (l74 < 262144); l74 = (l74 + 1)) {
			fVec22[l74] = 0.0;
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec66[l75] = 0.0;
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fVec23[l76] = 0.0;
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec65[l77] = 0.0;
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fVec24[l78] = 0.0;
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec67[l79] = 0.0;
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fVec25[l80] = 0.0;
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec68[l81] = 0.0;
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fVec26[l82] = 0.0;
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec69[l83] = 0.0;
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec4[l84] = 0.0;
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec70[l85] = 0.0;
		}
		for (int l86 = 0; (l86 < 1048576); l86 = (l86 + 1)) {
			fVec27[l86] = 0.0;
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			iRec71[l87] = 0;
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			iRec72[l88] = 0;
		}
		for (int l89 = 0; (l89 < 262144); l89 = (l89 + 1)) {
			fVec28[l89] = 0.0;
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec74[l90] = 0.0;
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fVec29[l91] = 0.0;
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec73[l92] = 0.0;
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fVec30[l93] = 0.0;
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec75[l94] = 0.0;
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			fVec31[l95] = 0.0;
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec76[l96] = 0.0;
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fVec32[l97] = 0.0;
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec77[l98] = 0.0;
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec5[l99] = 0.0;
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec78[l100] = 0.0;
		}
		for (int l101 = 0; (l101 < 1048576); l101 = (l101 + 1)) {
			fVec33[l101] = 0.0;
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			iRec79[l102] = 0;
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			iRec80[l103] = 0;
		}
		for (int l104 = 0; (l104 < 262144); l104 = (l104 + 1)) {
			fVec34[l104] = 0.0;
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec82[l105] = 0.0;
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fVec35[l106] = 0.0;
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec81[l107] = 0.0;
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fVec36[l108] = 0.0;
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			fRec83[l109] = 0.0;
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fVec37[l110] = 0.0;
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec84[l111] = 0.0;
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fVec38[l112] = 0.0;
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec85[l113] = 0.0;
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec6[l114] = 0.0;
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec86[l115] = 0.0;
		}
		for (int l116 = 0; (l116 < 1048576); l116 = (l116 + 1)) {
			fVec39[l116] = 0.0;
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			iRec87[l117] = 0;
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			iRec88[l118] = 0;
		}
		for (int l119 = 0; (l119 < 262144); l119 = (l119 + 1)) {
			fVec40[l119] = 0.0;
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec90[l120] = 0.0;
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fVec41[l121] = 0.0;
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec89[l122] = 0.0;
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fVec42[l123] = 0.0;
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			fRec91[l124] = 0.0;
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fVec43[l125] = 0.0;
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec92[l126] = 0.0;
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fVec44[l127] = 0.0;
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec93[l128] = 0.0;
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec7[l129] = 0.0;
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec94[l130] = 0.0;
		}
		for (int l131 = 0; (l131 < 1048576); l131 = (l131 + 1)) {
			fVec45[l131] = 0.0;
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			iRec95[l132] = 0;
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			iRec96[l133] = 0;
		}
		for (int l134 = 0; (l134 < 262144); l134 = (l134 + 1)) {
			fVec46[l134] = 0.0;
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec98[l135] = 0.0;
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fVec47[l136] = 0.0;
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			fRec97[l137] = 0.0;
		}
		for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) {
			fVec48[l138] = 0.0;
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			fRec99[l139] = 0.0;
		}
		for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			fVec49[l140] = 0.0;
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec100[l141] = 0.0;
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			fVec50[l142] = 0.0;
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec101[l143] = 0.0;
		}
		for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			fRec8[l144] = 0.0;
		}
		for (int l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			fRec102[l145] = 0.0;
		}
		for (int l146 = 0; (l146 < 1048576); l146 = (l146 + 1)) {
			fVec51[l146] = 0.0;
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			iRec103[l147] = 0;
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			iRec104[l148] = 0;
		}
		for (int l149 = 0; (l149 < 262144); l149 = (l149 + 1)) {
			fVec52[l149] = 0.0;
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			fRec106[l150] = 0.0;
		}
		for (int l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			fVec53[l151] = 0.0;
		}
		for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			fRec105[l152] = 0.0;
		}
		for (int l153 = 0; (l153 < 2); l153 = (l153 + 1)) {
			fVec54[l153] = 0.0;
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fRec107[l154] = 0.0;
		}
		for (int l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			fVec55[l155] = 0.0;
		}
		for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) {
			fRec108[l156] = 0.0;
		}
		for (int l157 = 0; (l157 < 2); l157 = (l157 + 1)) {
			fVec56[l157] = 0.0;
		}
		for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) {
			fRec109[l158] = 0.0;
		}
		for (int l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			fRec9[l159] = 0.0;
		}
		for (int l160 = 0; (l160 < 2); l160 = (l160 + 1)) {
			fRec110[l160] = 0.0;
		}
		for (int l161 = 0; (l161 < 1048576); l161 = (l161 + 1)) {
			fVec57[l161] = 0.0;
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			iRec111[l162] = 0;
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			iRec112[l163] = 0;
		}
		for (int l164 = 0; (l164 < 262144); l164 = (l164 + 1)) {
			fVec58[l164] = 0.0;
		}
		for (int l165 = 0; (l165 < 2); l165 = (l165 + 1)) {
			fRec114[l165] = 0.0;
		}
		for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			fVec59[l166] = 0.0;
		}
		for (int l167 = 0; (l167 < 2); l167 = (l167 + 1)) {
			fRec113[l167] = 0.0;
		}
		for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			fVec60[l168] = 0.0;
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			fRec115[l169] = 0.0;
		}
		for (int l170 = 0; (l170 < 2); l170 = (l170 + 1)) {
			fVec61[l170] = 0.0;
		}
		for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) {
			fRec116[l171] = 0.0;
		}
		for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			fVec62[l172] = 0.0;
		}
		for (int l173 = 0; (l173 < 2); l173 = (l173 + 1)) {
			fRec117[l173] = 0.0;
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fRec10[l174] = 0.0;
		}
		for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			fRec118[l175] = 0.0;
		}
		for (int l176 = 0; (l176 < 1048576); l176 = (l176 + 1)) {
			fVec63[l176] = 0.0;
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			iRec119[l177] = 0;
		}
		for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) {
			iRec120[l178] = 0;
		}
		for (int l179 = 0; (l179 < 262144); l179 = (l179 + 1)) {
			fVec64[l179] = 0.0;
		}
		for (int l180 = 0; (l180 < 2); l180 = (l180 + 1)) {
			fRec122[l180] = 0.0;
		}
		for (int l181 = 0; (l181 < 2); l181 = (l181 + 1)) {
			fVec65[l181] = 0.0;
		}
		for (int l182 = 0; (l182 < 2); l182 = (l182 + 1)) {
			fRec121[l182] = 0.0;
		}
		for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			fVec66[l183] = 0.0;
		}
		for (int l184 = 0; (l184 < 2); l184 = (l184 + 1)) {
			fRec123[l184] = 0.0;
		}
		for (int l185 = 0; (l185 < 2); l185 = (l185 + 1)) {
			fVec67[l185] = 0.0;
		}
		for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			fRec124[l186] = 0.0;
		}
		for (int l187 = 0; (l187 < 2); l187 = (l187 + 1)) {
			fVec68[l187] = 0.0;
		}
		for (int l188 = 0; (l188 < 2); l188 = (l188 + 1)) {
			fRec125[l188] = 0.0;
		}
		for (int l189 = 0; (l189 < 2); l189 = (l189 + 1)) {
			fRec11[l189] = 0.0;
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			fRec126[l190] = 0.0;
		}
		for (int l191 = 0; (l191 < 1048576); l191 = (l191 + 1)) {
			fVec69[l191] = 0.0;
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			iRec127[l192] = 0;
		}
		for (int l193 = 0; (l193 < 2); l193 = (l193 + 1)) {
			iRec128[l193] = 0;
		}
		for (int l194 = 0; (l194 < 262144); l194 = (l194 + 1)) {
			fVec70[l194] = 0.0;
		}
		for (int l195 = 0; (l195 < 2); l195 = (l195 + 1)) {
			fRec130[l195] = 0.0;
		}
		for (int l196 = 0; (l196 < 2); l196 = (l196 + 1)) {
			fVec71[l196] = 0.0;
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			fRec129[l197] = 0.0;
		}
		for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) {
			fVec72[l198] = 0.0;
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			fRec131[l199] = 0.0;
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			fVec73[l200] = 0.0;
		}
		for (int l201 = 0; (l201 < 2); l201 = (l201 + 1)) {
			fRec132[l201] = 0.0;
		}
		for (int l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			fVec74[l202] = 0.0;
		}
		for (int l203 = 0; (l203 < 2); l203 = (l203 + 1)) {
			fRec133[l203] = 0.0;
		}
		for (int l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			fRec12[l204] = 0.0;
		}
		for (int l205 = 0; (l205 < 2); l205 = (l205 + 1)) {
			fRec134[l205] = 0.0;
		}
		for (int l206 = 0; (l206 < 1048576); l206 = (l206 + 1)) {
			fVec75[l206] = 0.0;
		}
		for (int l207 = 0; (l207 < 2); l207 = (l207 + 1)) {
			iRec135[l207] = 0;
		}
		for (int l208 = 0; (l208 < 2); l208 = (l208 + 1)) {
			iRec136[l208] = 0;
		}
		for (int l209 = 0; (l209 < 262144); l209 = (l209 + 1)) {
			fVec76[l209] = 0.0;
		}
		for (int l210 = 0; (l210 < 2); l210 = (l210 + 1)) {
			fRec138[l210] = 0.0;
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			fVec77[l211] = 0.0;
		}
		for (int l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			fRec137[l212] = 0.0;
		}
		for (int l213 = 0; (l213 < 2); l213 = (l213 + 1)) {
			fVec78[l213] = 0.0;
		}
		for (int l214 = 0; (l214 < 2); l214 = (l214 + 1)) {
			fRec139[l214] = 0.0;
		}
		for (int l215 = 0; (l215 < 2); l215 = (l215 + 1)) {
			fVec79[l215] = 0.0;
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			fRec140[l216] = 0.0;
		}
		for (int l217 = 0; (l217 < 2); l217 = (l217 + 1)) {
			fVec80[l217] = 0.0;
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fRec141[l218] = 0.0;
		}
		for (int l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			fRec13[l219] = 0.0;
		}
		for (int l220 = 0; (l220 < 2); l220 = (l220 + 1)) {
			fRec142[l220] = 0.0;
		}
		for (int l221 = 0; (l221 < 1048576); l221 = (l221 + 1)) {
			fVec81[l221] = 0.0;
		}
		for (int l222 = 0; (l222 < 2); l222 = (l222 + 1)) {
			iRec143[l222] = 0;
		}
		for (int l223 = 0; (l223 < 2); l223 = (l223 + 1)) {
			iRec144[l223] = 0;
		}
		for (int l224 = 0; (l224 < 262144); l224 = (l224 + 1)) {
			fVec82[l224] = 0.0;
		}
		for (int l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			fRec146[l225] = 0.0;
		}
		for (int l226 = 0; (l226 < 2); l226 = (l226 + 1)) {
			fVec83[l226] = 0.0;
		}
		for (int l227 = 0; (l227 < 2); l227 = (l227 + 1)) {
			fRec145[l227] = 0.0;
		}
		for (int l228 = 0; (l228 < 2); l228 = (l228 + 1)) {
			fVec84[l228] = 0.0;
		}
		for (int l229 = 0; (l229 < 2); l229 = (l229 + 1)) {
			fRec147[l229] = 0.0;
		}
		for (int l230 = 0; (l230 < 2); l230 = (l230 + 1)) {
			fVec85[l230] = 0.0;
		}
		for (int l231 = 0; (l231 < 2); l231 = (l231 + 1)) {
			fRec148[l231] = 0.0;
		}
		for (int l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			fVec86[l232] = 0.0;
		}
		for (int l233 = 0; (l233 < 2); l233 = (l233 + 1)) {
			fRec149[l233] = 0.0;
		}
		for (int l234 = 0; (l234 < 2); l234 = (l234 + 1)) {
			fRec14[l234] = 0.0;
		}
		for (int l235 = 0; (l235 < 2); l235 = (l235 + 1)) {
			fRec150[l235] = 0.0;
		}
		for (int l236 = 0; (l236 < 1048576); l236 = (l236 + 1)) {
			fVec87[l236] = 0.0;
		}
		for (int l237 = 0; (l237 < 2); l237 = (l237 + 1)) {
			iRec151[l237] = 0;
		}
		for (int l238 = 0; (l238 < 2); l238 = (l238 + 1)) {
			iRec152[l238] = 0;
		}
		for (int l239 = 0; (l239 < 262144); l239 = (l239 + 1)) {
			fVec88[l239] = 0.0;
		}
		for (int l240 = 0; (l240 < 2); l240 = (l240 + 1)) {
			fRec154[l240] = 0.0;
		}
		for (int l241 = 0; (l241 < 2); l241 = (l241 + 1)) {
			fVec89[l241] = 0.0;
		}
		for (int l242 = 0; (l242 < 2); l242 = (l242 + 1)) {
			fRec153[l242] = 0.0;
		}
		for (int l243 = 0; (l243 < 2); l243 = (l243 + 1)) {
			fVec90[l243] = 0.0;
		}
		for (int l244 = 0; (l244 < 2); l244 = (l244 + 1)) {
			fRec155[l244] = 0.0;
		}
		for (int l245 = 0; (l245 < 2); l245 = (l245 + 1)) {
			fVec91[l245] = 0.0;
		}
		for (int l246 = 0; (l246 < 2); l246 = (l246 + 1)) {
			fRec156[l246] = 0.0;
		}
		for (int l247 = 0; (l247 < 2); l247 = (l247 + 1)) {
			fVec92[l247] = 0.0;
		}
		for (int l248 = 0; (l248 < 2); l248 = (l248 + 1)) {
			fRec157[l248] = 0.0;
		}
		for (int l249 = 0; (l249 < 2); l249 = (l249 + 1)) {
			fRec15[l249] = 0.0;
		}
		for (int l250 = 0; (l250 < 2); l250 = (l250 + 1)) {
			fRec158[l250] = 0.0;
		}
		for (int l251 = 0; (l251 < 1048576); l251 = (l251 + 1)) {
			fVec93[l251] = 0.0;
		}
		for (int l252 = 0; (l252 < 2); l252 = (l252 + 1)) {
			iRec159[l252] = 0;
		}
		for (int l253 = 0; (l253 < 2); l253 = (l253 + 1)) {
			iRec160[l253] = 0;
		}
		for (int l254 = 0; (l254 < 262144); l254 = (l254 + 1)) {
			fVec94[l254] = 0.0;
		}
		for (int l255 = 0; (l255 < 2); l255 = (l255 + 1)) {
			fRec162[l255] = 0.0;
		}
		for (int l256 = 0; (l256 < 2); l256 = (l256 + 1)) {
			fVec95[l256] = 0.0;
		}
		for (int l257 = 0; (l257 < 2); l257 = (l257 + 1)) {
			fRec161[l257] = 0.0;
		}
		for (int l258 = 0; (l258 < 2); l258 = (l258 + 1)) {
			fVec96[l258] = 0.0;
		}
		for (int l259 = 0; (l259 < 2); l259 = (l259 + 1)) {
			fRec163[l259] = 0.0;
		}
		for (int l260 = 0; (l260 < 2); l260 = (l260 + 1)) {
			fVec97[l260] = 0.0;
		}
		for (int l261 = 0; (l261 < 2); l261 = (l261 + 1)) {
			fRec164[l261] = 0.0;
		}
		for (int l262 = 0; (l262 < 2); l262 = (l262 + 1)) {
			fVec98[l262] = 0.0;
		}
		for (int l263 = 0; (l263 < 2); l263 = (l263 + 1)) {
			fRec165[l263] = 0.0;
		}
		for (int l264 = 0; (l264 < 2); l264 = (l264 + 1)) {
			fRec16[l264] = 0.0;
		}
		for (int l265 = 0; (l265 < 2); l265 = (l265 + 1)) {
			fRec166[l265] = 0.0;
		}
		for (int l266 = 0; (l266 < 2); l266 = (l266 + 1)) {
			fRec167[l266] = 0.0;
		}
		for (int l267 = 0; (l267 < 2); l267 = (l267 + 1)) {
			fRec168[l267] = 0.0;
		}
		for (int l268 = 0; (l268 < 2); l268 = (l268 + 1)) {
			fRec169[l268] = 0.0;
		}
		for (int l269 = 0; (l269 < 2); l269 = (l269 + 1)) {
			fRec170[l269] = 0.0;
		}
		for (int l270 = 0; (l270 < 2); l270 = (l270 + 1)) {
			fRec171[l270] = 0.0;
		}
		for (int l271 = 0; (l271 < 2); l271 = (l271 + 1)) {
			fRec172[l271] = 0.0;
		}
		for (int l272 = 0; (l272 < 2); l272 = (l272 + 1)) {
			fRec173[l272] = 0.0;
		}
		for (int l273 = 0; (l273 < 2); l273 = (l273 + 1)) {
			fRec174[l273] = 0.0;
		}
		for (int l274 = 0; (l274 < 2); l274 = (l274 + 1)) {
			fRec175[l274] = 0.0;
		}
		for (int l275 = 0; (l275 < 2); l275 = (l275 + 1)) {
			fRec176[l275] = 0.0;
		}
		for (int l276 = 0; (l276 < 2); l276 = (l276 + 1)) {
			fRec177[l276] = 0.0;
		}
		for (int l277 = 0; (l277 < 2); l277 = (l277 + 1)) {
			fRec178[l277] = 0.0;
		}
		for (int l278 = 0; (l278 < 2); l278 = (l278 + 1)) {
			fRec179[l278] = 0.0;
		}
		for (int l279 = 0; (l279 < 2); l279 = (l279 + 1)) {
			fRec180[l279] = 0.0;
		}
		for (int l280 = 0; (l280 < 2); l280 = (l280 + 1)) {
			fRec181[l280] = 0.0;
		}
		for (int l281 = 0; (l281 < 2); l281 = (l281 + 1)) {
			fRec182[l281] = 0.0;
		}
		for (int l282 = 0; (l282 < 2); l282 = (l282 + 1)) {
			fRec183[l282] = 0.0;
		}
		for (int l283 = 0; (l283 < 2); l283 = (l283 + 1)) {
			fRec184[l283] = 0.0;
		}
		for (int l284 = 0; (l284 < 2); l284 = (l284 + 1)) {
			fRec185[l284] = 0.0;
		}
		for (int l285 = 0; (l285 < 2); l285 = (l285 + 1)) {
			fRec186[l285] = 0.0;
		}
		for (int l286 = 0; (l286 < 2); l286 = (l286 + 1)) {
			fRec187[l286] = 0.0;
		}
		for (int l287 = 0; (l287 < 2); l287 = (l287 + 1)) {
			fRec188[l287] = 0.0;
		}
		for (int l288 = 0; (l288 < 2); l288 = (l288 + 1)) {
			fRec189[l288] = 0.0;
		}
		for (int l289 = 0; (l289 < 2); l289 = (l289 + 1)) {
			fRec190[l289] = 0.0;
		}
		for (int l290 = 0; (l290 < 2); l290 = (l290 + 1)) {
			fRec191[l290] = 0.0;
		}
		for (int l291 = 0; (l291 < 2); l291 = (l291 + 1)) {
			fRec192[l291] = 0.0;
		}
		for (int l292 = 0; (l292 < 2); l292 = (l292 + 1)) {
			fRec193[l292] = 0.0;
		}
		for (int l293 = 0; (l293 < 2); l293 = (l293 + 1)) {
			fRec194[l293] = 0.0;
		}
		for (int l294 = 0; (l294 < 2); l294 = (l294 + 1)) {
			fRec195[l294] = 0.0;
		}
		for (int l295 = 0; (l295 < 2); l295 = (l295 + 1)) {
			fRec196[l295] = 0.0;
		}
		for (int l296 = 0; (l296 < 2); l296 = (l296 + 1)) {
			fRec197[l296] = 0.0;
		}
		for (int l297 = 0; (l297 < 2); l297 = (l297 + 1)) {
			fRec198[l297] = 0.0;
		}
		for (int l298 = 0; (l298 < 2); l298 = (l298 + 1)) {
			fRec199[l298] = 0.0;
		}
		for (int l299 = 0; (l299 < 2); l299 = (l299 + 1)) {
			fRec200[l299] = 0.0;
		}
		for (int l300 = 0; (l300 < 2); l300 = (l300 + 1)) {
			fRec201[l300] = 0.0;
		}
		for (int l301 = 0; (l301 < 2); l301 = (l301 + 1)) {
			fRec202[l301] = 0.0;
		}
		for (int l302 = 0; (l302 < 2); l302 = (l302 + 1)) {
			fRec203[l302] = 0.0;
		}
		for (int l303 = 0; (l303 < 2); l303 = (l303 + 1)) {
			fRec204[l303] = 0.0;
		}
		for (int l304 = 0; (l304 < 2); l304 = (l304 + 1)) {
			fRec205[l304] = 0.0;
		}
		for (int l305 = 0; (l305 < 2); l305 = (l305 + 1)) {
			fRec206[l305] = 0.0;
		}
		for (int l306 = 0; (l306 < 2); l306 = (l306 + 1)) {
			fRec207[l306] = 0.0;
		}
		for (int l307 = 0; (l307 < 2); l307 = (l307 + 1)) {
			fRec208[l307] = 0.0;
		}
		for (int l308 = 0; (l308 < 2); l308 = (l308 + 1)) {
			fRec209[l308] = 0.0;
		}
		for (int l309 = 0; (l309 < 2); l309 = (l309 + 1)) {
			fRec210[l309] = 0.0;
		}
		for (int l310 = 0; (l310 < 2); l310 = (l310 + 1)) {
			fRec211[l310] = 0.0;
		}
		for (int l311 = 0; (l311 < 2); l311 = (l311 + 1)) {
			fRec212[l311] = 0.0;
		}
		for (int l312 = 0; (l312 < 2); l312 = (l312 + 1)) {
			fRec213[l312] = 0.0;
		}
		for (int l313 = 0; (l313 < 2); l313 = (l313 + 1)) {
			fRec214[l313] = 0.0;
		}
		for (int l314 = 0; (l314 < 2); l314 = (l314 + 1)) {
			fRec215[l314] = 0.0;
		}
		for (int l315 = 0; (l315 < 2); l315 = (l315 + 1)) {
			fRec216[l315] = 0.0;
		}
		for (int l316 = 0; (l316 < 2); l316 = (l316 + 1)) {
			fRec217[l316] = 0.0;
		}
		for (int l317 = 0; (l317 < 2); l317 = (l317 + 1)) {
			fRec218[l317] = 0.0;
		}
		for (int l318 = 0; (l318 < 2); l318 = (l318 + 1)) {
			fRec219[l318] = 0.0;
		}
		for (int l319 = 0; (l319 < 2); l319 = (l319 + 1)) {
			fRec220[l319] = 0.0;
		}
		for (int l320 = 0; (l320 < 2); l320 = (l320 + 1)) {
			fRec221[l320] = 0.0;
		}
		for (int l321 = 0; (l321 < 2); l321 = (l321 + 1)) {
			fRec222[l321] = 0.0;
		}
		for (int l322 = 0; (l322 < 2); l322 = (l322 + 1)) {
			fRec223[l322] = 0.0;
		}
		for (int l323 = 0; (l323 < 2); l323 = (l323 + 1)) {
			fRec224[l323] = 0.0;
		}
		for (int l324 = 0; (l324 < 2); l324 = (l324 + 1)) {
			fRec225[l324] = 0.0;
		}
		for (int l325 = 0; (l325 < 2); l325 = (l325 + 1)) {
			fRec226[l325] = 0.0;
		}
		for (int l326 = 0; (l326 < 2); l326 = (l326 + 1)) {
			fRec227[l326] = 0.0;
		}
		for (int l327 = 0; (l327 < 2); l327 = (l327 + 1)) {
			fRec228[l327] = 0.0;
		}
		for (int l328 = 0; (l328 < 2); l328 = (l328 + 1)) {
			fRec229[l328] = 0.0;
		}
		for (int l329 = 0; (l329 < 2); l329 = (l329 + 1)) {
			fRec230[l329] = 0.0;
		}
		for (int l330 = 0; (l330 < 2); l330 = (l330 + 1)) {
			fRec231[l330] = 0.0;
		}
		for (int l331 = 0; (l331 < 2); l331 = (l331 + 1)) {
			fRec232[l331] = 0.0;
		}
		for (int l332 = 0; (l332 < 2); l332 = (l332 + 1)) {
			fRec233[l332] = 0.0;
		}
		for (int l333 = 0; (l333 < 2); l333 = (l333 + 1)) {
			fRec234[l333] = 0.0;
		}
		for (int l334 = 0; (l334 < 2); l334 = (l334 + 1)) {
			fRec235[l334] = 0.0;
		}
		for (int l335 = 0; (l335 < 2); l335 = (l335 + 1)) {
			fRec236[l335] = 0.0;
		}
		for (int l336 = 0; (l336 < 2); l336 = (l336 + 1)) {
			fRec237[l336] = 0.0;
		}
		for (int l337 = 0; (l337 < 2); l337 = (l337 + 1)) {
			fRec238[l337] = 0.0;
		}
		for (int l338 = 0; (l338 < 2); l338 = (l338 + 1)) {
			fRec239[l338] = 0.0;
		}
		for (int l339 = 0; (l339 < 2); l339 = (l339 + 1)) {
			fRec240[l339] = 0.0;
		}
		for (int l340 = 0; (l340 < 2); l340 = (l340 + 1)) {
			fRec241[l340] = 0.0;
		}
		for (int l341 = 0; (l341 < 2); l341 = (l341 + 1)) {
			fRec242[l341] = 0.0;
		}
		for (int l342 = 0; (l342 < 2); l342 = (l342 + 1)) {
			fRec243[l342] = 0.0;
		}
		for (int l343 = 0; (l343 < 2); l343 = (l343 + 1)) {
			fRec244[l343] = 0.0;
		}
		for (int l344 = 0; (l344 < 2); l344 = (l344 + 1)) {
			fRec245[l344] = 0.0;
		}
		for (int l345 = 0; (l345 < 2); l345 = (l345 + 1)) {
			fRec246[l345] = 0.0;
		}
		for (int l346 = 0; (l346 < 2); l346 = (l346 + 1)) {
			fRec247[l346] = 0.0;
		}
		for (int l347 = 0; (l347 < 2); l347 = (l347 + 1)) {
			fRec248[l347] = 0.0;
		}
		for (int l348 = 0; (l348 < 2); l348 = (l348 + 1)) {
			fRec249[l348] = 0.0;
		}
		for (int l349 = 0; (l349 < 2); l349 = (l349 + 1)) {
			fRec250[l349] = 0.0;
		}
		for (int l350 = 0; (l350 < 2); l350 = (l350 + 1)) {
			fRec251[l350] = 0.0;
		}
		for (int l351 = 0; (l351 < 2); l351 = (l351 + 1)) {
			fRec252[l351] = 0.0;
		}
		for (int l352 = 0; (l352 < 2); l352 = (l352 + 1)) {
			fRec253[l352] = 0.0;
		}
		for (int l353 = 0; (l353 < 2); l353 = (l353 + 1)) {
			fRec254[l353] = 0.0;
		}
		for (int l354 = 0; (l354 < 2); l354 = (l354 + 1)) {
			fRec255[l354] = 0.0;
		}
		for (int l355 = 0; (l355 < 2); l355 = (l355 + 1)) {
			fRec256[l355] = 0.0;
		}
		for (int l356 = 0; (l356 < 2); l356 = (l356 + 1)) {
			fRec257[l356] = 0.0;
		}
		for (int l357 = 0; (l357 < 2); l357 = (l357 + 1)) {
			fRec258[l357] = 0.0;
		}
		for (int l358 = 0; (l358 < 2); l358 = (l358 + 1)) {
			fRec259[l358] = 0.0;
		}
		for (int l359 = 0; (l359 < 2); l359 = (l359 + 1)) {
			fRec260[l359] = 0.0;
		}
		for (int l360 = 0; (l360 < 2); l360 = (l360 + 1)) {
			fRec261[l360] = 0.0;
		}
		for (int l361 = 0; (l361 < 2); l361 = (l361 + 1)) {
			fRec262[l361] = 0.0;
		}
		for (int l362 = 0; (l362 < 2); l362 = (l362 + 1)) {
			fRec263[l362] = 0.0;
		}
		for (int l363 = 0; (l363 < 2); l363 = (l363 + 1)) {
			fRec264[l363] = 0.0;
		}
		for (int l364 = 0; (l364 < 2); l364 = (l364 + 1)) {
			fRec265[l364] = 0.0;
		}
		for (int l365 = 0; (l365 < 2); l365 = (l365 + 1)) {
			fRec266[l365] = 0.0;
		}
		for (int l366 = 0; (l366 < 2); l366 = (l366 + 1)) {
			fRec267[l366] = 0.0;
		}
		for (int l367 = 0; (l367 < 2); l367 = (l367 + 1)) {
			fRec268[l367] = 0.0;
		}
		for (int l368 = 0; (l368 < 2); l368 = (l368 + 1)) {
			fRec269[l368] = 0.0;
		}
		for (int l369 = 0; (l369 < 2); l369 = (l369 + 1)) {
			fRec271[l369] = 0.0;
		}
		for (int l370 = 0; (l370 < 2); l370 = (l370 + 1)) {
			iRec272[l370] = 0;
		}
		for (int l371 = 0; (l371 < 2); l371 = (l371 + 1)) {
			iRec270[l371] = 0;
		}
		for (int l372 = 0; (l372 < 2); l372 = (l372 + 1)) {
			fRec278[l372] = 0.0;
		}
		for (int l373 = 0; (l373 < 2); l373 = (l373 + 1)) {
			fRec279[l373] = 0.0;
		}
		for (int l374 = 0; (l374 < 2); l374 = (l374 + 1)) {
			fRec280[l374] = 0.0;
		}
		for (int l375 = 0; (l375 < 2); l375 = (l375 + 1)) {
			fRec281[l375] = 0.0;
		}
		for (int l376 = 0; (l376 < 2); l376 = (l376 + 1)) {
			fRec282[l376] = 0.0;
		}
		for (int l377 = 0; (l377 < 2); l377 = (l377 + 1)) {
			fRec283[l377] = 0.0;
		}
		for (int l378 = 0; (l378 < 2); l378 = (l378 + 1)) {
			fRec284[l378] = 0.0;
		}
		for (int l379 = 0; (l379 < 2); l379 = (l379 + 1)) {
			fRec285[l379] = 0.0;
		}
		for (int l380 = 0; (l380 < 2); l380 = (l380 + 1)) {
			fRec286[l380] = 0.0;
		}
		for (int l381 = 0; (l381 < 2); l381 = (l381 + 1)) {
			fRec287[l381] = 0.0;
		}
		for (int l382 = 0; (l382 < 2); l382 = (l382 + 1)) {
			fRec288[l382] = 0.0;
		}
		for (int l383 = 0; (l383 < 2); l383 = (l383 + 1)) {
			fRec289[l383] = 0.0;
		}
		for (int l384 = 0; (l384 < 2); l384 = (l384 + 1)) {
			fRec290[l384] = 0.0;
		}
		for (int l385 = 0; (l385 < 2); l385 = (l385 + 1)) {
			fRec291[l385] = 0.0;
		}
		for (int l386 = 0; (l386 < 2); l386 = (l386 + 1)) {
			fRec292[l386] = 0.0;
		}
		for (int l387 = 0; (l387 < 2); l387 = (l387 + 1)) {
			fRec293[l387] = 0.0;
		}
		for (int l388 = 0; (l388 < 2); l388 = (l388 + 1)) {
			fRec294[l388] = 0.0;
		}
		for (int l389 = 0; (l389 < 2); l389 = (l389 + 1)) {
			fRec295[l389] = 0.0;
		}
		for (int l390 = 0; (l390 < 2); l390 = (l390 + 1)) {
			fRec296[l390] = 0.0;
		}
		for (int l391 = 0; (l391 < 2); l391 = (l391 + 1)) {
			fRec297[l391] = 0.0;
		}
		for (int l392 = 0; (l392 < 2); l392 = (l392 + 1)) {
			fRec298[l392] = 0.0;
		}
		for (int l393 = 0; (l393 < 2); l393 = (l393 + 1)) {
			iRec299[l393] = 0;
		}
		for (int l394 = 0; (l394 < 2); l394 = (l394 + 1)) {
			fRec300[l394] = 0.0;
		}
		for (int l395 = 0; (l395 < 2); l395 = (l395 + 1)) {
			fRec301[l395] = 0.0;
		}
		for (int l396 = 0; (l396 < 2); l396 = (l396 + 1)) {
			fRec302[l396] = 0.0;
		}
		for (int l397 = 0; (l397 < 2); l397 = (l397 + 1)) {
			fRec303[l397] = 0.0;
		}
		for (int l398 = 0; (l398 < 2); l398 = (l398 + 1)) {
			fRec304[l398] = 0.0;
		}
		for (int l399 = 0; (l399 < 2); l399 = (l399 + 1)) {
			fRec305[l399] = 0.0;
		}
		for (int l400 = 0; (l400 < 2); l400 = (l400 + 1)) {
			fRec306[l400] = 0.0;
		}
		for (int l401 = 0; (l401 < 2); l401 = (l401 + 1)) {
			fRec307[l401] = 0.0;
		}
		for (int l402 = 0; (l402 < 2); l402 = (l402 + 1)) {
			fRec308[l402] = 0.0;
		}
		for (int l403 = 0; (l403 < 2); l403 = (l403 + 1)) {
			fRec309[l403] = 0.0;
		}
		for (int l404 = 0; (l404 < 2); l404 = (l404 + 1)) {
			fRec310[l404] = 0.0;
		}
		for (int l405 = 0; (l405 < 2); l405 = (l405 + 1)) {
			fRec311[l405] = 0.0;
		}
		for (int l406 = 0; (l406 < 2); l406 = (l406 + 1)) {
			fRec312[l406] = 0.0;
		}
		for (int l407 = 0; (l407 < 2); l407 = (l407 + 1)) {
			fRec313[l407] = 0.0;
		}
		for (int l408 = 0; (l408 < 2); l408 = (l408 + 1)) {
			fRec314[l408] = 0.0;
		}
		for (int l409 = 0; (l409 < 2); l409 = (l409 + 1)) {
			fRec315[l409] = 0.0;
		}
		for (int l410 = 0; (l410 < 2); l410 = (l410 + 1)) {
			fRec316[l410] = 0.0;
		}
		for (int l411 = 0; (l411 < 2); l411 = (l411 + 1)) {
			iRec317[l411] = 0;
		}
		for (int l412 = 0; (l412 < 2); l412 = (l412 + 1)) {
			fRec318[l412] = 0.0;
		}
		for (int l413 = 0; (l413 < 2); l413 = (l413 + 1)) {
			fRec319[l413] = 0.0;
		}
		for (int l414 = 0; (l414 < 2); l414 = (l414 + 1)) {
			fRec320[l414] = 0.0;
		}
		for (int l415 = 0; (l415 < 2); l415 = (l415 + 1)) {
			fRec321[l415] = 0.0;
		}
		for (int l416 = 0; (l416 < 2); l416 = (l416 + 1)) {
			fRec322[l416] = 0.0;
		}
		for (int l417 = 0; (l417 < 2); l417 = (l417 + 1)) {
			fRec323[l417] = 0.0;
		}
		for (int l418 = 0; (l418 < 2); l418 = (l418 + 1)) {
			fRec324[l418] = 0.0;
		}
		for (int l419 = 0; (l419 < 2); l419 = (l419 + 1)) {
			fRec325[l419] = 0.0;
		}
		for (int l420 = 0; (l420 < 2); l420 = (l420 + 1)) {
			fRec326[l420] = 0.0;
		}
		for (int l421 = 0; (l421 < 2); l421 = (l421 + 1)) {
			fRec327[l421] = 0.0;
		}
		for (int l422 = 0; (l422 < 2); l422 = (l422 + 1)) {
			fRec328[l422] = 0.0;
		}
		for (int l423 = 0; (l423 < 2); l423 = (l423 + 1)) {
			fRec329[l423] = 0.0;
		}
		for (int l424 = 0; (l424 < 2); l424 = (l424 + 1)) {
			fRec330[l424] = 0.0;
		}
		for (int l425 = 0; (l425 < 2); l425 = (l425 + 1)) {
			fRec331[l425] = 0.0;
		}
		for (int l426 = 0; (l426 < 2); l426 = (l426 + 1)) {
			fRec332[l426] = 0.0;
		}
		for (int l427 = 0; (l427 < 2); l427 = (l427 + 1)) {
			fRec333[l427] = 0.0;
		}
		for (int l428 = 0; (l428 < 2); l428 = (l428 + 1)) {
			fRec334[l428] = 0.0;
		}
		for (int l429 = 0; (l429 < 2); l429 = (l429 + 1)) {
			iRec335[l429] = 0;
		}
		for (int l430 = 0; (l430 < 2); l430 = (l430 + 1)) {
			fRec336[l430] = 0.0;
		}
		for (int l431 = 0; (l431 < 2); l431 = (l431 + 1)) {
			fRec337[l431] = 0.0;
		}
		for (int l432 = 0; (l432 < 2); l432 = (l432 + 1)) {
			fRec338[l432] = 0.0;
		}
		for (int l433 = 0; (l433 < 2); l433 = (l433 + 1)) {
			fRec339[l433] = 0.0;
		}
		for (int l434 = 0; (l434 < 2); l434 = (l434 + 1)) {
			fRec340[l434] = 0.0;
		}
		for (int l435 = 0; (l435 < 2); l435 = (l435 + 1)) {
			fRec341[l435] = 0.0;
		}
		for (int l436 = 0; (l436 < 2); l436 = (l436 + 1)) {
			fRec342[l436] = 0.0;
		}
		for (int l437 = 0; (l437 < 2); l437 = (l437 + 1)) {
			fRec343[l437] = 0.0;
		}
		for (int l438 = 0; (l438 < 2); l438 = (l438 + 1)) {
			fRec344[l438] = 0.0;
		}
		for (int l439 = 0; (l439 < 2); l439 = (l439 + 1)) {
			fRec345[l439] = 0.0;
		}
		for (int l440 = 0; (l440 < 2); l440 = (l440 + 1)) {
			fRec346[l440] = 0.0;
		}
		for (int l441 = 0; (l441 < 2); l441 = (l441 + 1)) {
			fRec347[l441] = 0.0;
		}
		for (int l442 = 0; (l442 < 2); l442 = (l442 + 1)) {
			fRec348[l442] = 0.0;
		}
		for (int l443 = 0; (l443 < 2); l443 = (l443 + 1)) {
			fRec349[l443] = 0.0;
		}
		for (int l444 = 0; (l444 < 2); l444 = (l444 + 1)) {
			fRec350[l444] = 0.0;
		}
		for (int l445 = 0; (l445 < 2); l445 = (l445 + 1)) {
			fRec351[l445] = 0.0;
		}
		for (int l446 = 0; (l446 < 2); l446 = (l446 + 1)) {
			fRec352[l446] = 0.0;
		}
		for (int l447 = 0; (l447 < 2); l447 = (l447 + 1)) {
			iRec353[l447] = 0;
		}
		for (int l448 = 0; (l448 < 2); l448 = (l448 + 1)) {
			fRec354[l448] = 0.0;
		}
		for (int l449 = 0; (l449 < 2); l449 = (l449 + 1)) {
			fRec355[l449] = 0.0;
		}
		for (int l450 = 0; (l450 < 2); l450 = (l450 + 1)) {
			fRec356[l450] = 0.0;
		}
		for (int l451 = 0; (l451 < 2); l451 = (l451 + 1)) {
			fRec357[l451] = 0.0;
		}
		for (int l452 = 0; (l452 < 2); l452 = (l452 + 1)) {
			fRec358[l452] = 0.0;
		}
		for (int l453 = 0; (l453 < 2); l453 = (l453 + 1)) {
			fRec359[l453] = 0.0;
		}
		for (int l454 = 0; (l454 < 2); l454 = (l454 + 1)) {
			fRec360[l454] = 0.0;
		}
		for (int l455 = 0; (l455 < 2); l455 = (l455 + 1)) {
			fRec361[l455] = 0.0;
		}
		for (int l456 = 0; (l456 < 2); l456 = (l456 + 1)) {
			fRec362[l456] = 0.0;
		}
		for (int l457 = 0; (l457 < 2); l457 = (l457 + 1)) {
			fRec363[l457] = 0.0;
		}
		for (int l458 = 0; (l458 < 2); l458 = (l458 + 1)) {
			fRec364[l458] = 0.0;
		}
		for (int l459 = 0; (l459 < 2); l459 = (l459 + 1)) {
			fRec365[l459] = 0.0;
		}
		for (int l460 = 0; (l460 < 2); l460 = (l460 + 1)) {
			fRec366[l460] = 0.0;
		}
		for (int l461 = 0; (l461 < 2); l461 = (l461 + 1)) {
			fRec367[l461] = 0.0;
		}
		for (int l462 = 0; (l462 < 2); l462 = (l462 + 1)) {
			fRec368[l462] = 0.0;
		}
		for (int l463 = 0; (l463 < 2); l463 = (l463 + 1)) {
			fRec369[l463] = 0.0;
		}
		for (int l464 = 0; (l464 < 2); l464 = (l464 + 1)) {
			fRec370[l464] = 0.0;
		}
		for (int l465 = 0; (l465 < 2); l465 = (l465 + 1)) {
			iRec371[l465] = 0;
		}
		for (int l466 = 0; (l466 < 2); l466 = (l466 + 1)) {
			fRec372[l466] = 0.0;
		}
		for (int l467 = 0; (l467 < 2); l467 = (l467 + 1)) {
			fRec373[l467] = 0.0;
		}
		for (int l468 = 0; (l468 < 2); l468 = (l468 + 1)) {
			fRec374[l468] = 0.0;
		}
		for (int l469 = 0; (l469 < 2); l469 = (l469 + 1)) {
			fRec375[l469] = 0.0;
		}
		for (int l470 = 0; (l470 < 2); l470 = (l470 + 1)) {
			fRec376[l470] = 0.0;
		}
		for (int l471 = 0; (l471 < 2); l471 = (l471 + 1)) {
			fRec377[l471] = 0.0;
		}
		for (int l472 = 0; (l472 < 2); l472 = (l472 + 1)) {
			fRec378[l472] = 0.0;
		}
		for (int l473 = 0; (l473 < 2); l473 = (l473 + 1)) {
			fRec379[l473] = 0.0;
		}
		for (int l474 = 0; (l474 < 2); l474 = (l474 + 1)) {
			fRec380[l474] = 0.0;
		}
		for (int l475 = 0; (l475 < 2); l475 = (l475 + 1)) {
			fRec381[l475] = 0.0;
		}
		for (int l476 = 0; (l476 < 2); l476 = (l476 + 1)) {
			fRec382[l476] = 0.0;
		}
		for (int l477 = 0; (l477 < 2); l477 = (l477 + 1)) {
			fRec383[l477] = 0.0;
		}
		for (int l478 = 0; (l478 < 2); l478 = (l478 + 1)) {
			fRec384[l478] = 0.0;
		}
		for (int l479 = 0; (l479 < 2); l479 = (l479 + 1)) {
			fRec385[l479] = 0.0;
		}
		for (int l480 = 0; (l480 < 2); l480 = (l480 + 1)) {
			fRec386[l480] = 0.0;
		}
		for (int l481 = 0; (l481 < 2); l481 = (l481 + 1)) {
			fRec387[l481] = 0.0;
		}
		for (int l482 = 0; (l482 < 2); l482 = (l482 + 1)) {
			fRec388[l482] = 0.0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual FilDeSoi1PanStereo* clone() {
		return new FilDeSoi1PanStereo();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FilDeSoi1PanStereo");
		ui_interface->openHorizontalBox("Encoders");
		ui_interface->addHorizontalSlider("rotfreq0", &fHslider113, 0.10000000000000001, -10.0, 10.0, 0.01);
		ui_interface->addHorizontalSlider("rotfreq1", &fHslider111, 0.10000000000000001, -10.0, 10.0, 0.01);
		ui_interface->addHorizontalSlider("rotfreq2", &fHslider109, 0.10000000000000001, -10.0, 10.0, 0.01);
		ui_interface->addHorizontalSlider("rotfreq3", &fHslider107, 0.10000000000000001, -10.0, 10.0, 0.01);
		ui_interface->addHorizontalSlider("rotphase0", &fHslider112, 0.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("rotphase1", &fHslider110, 0.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("rotphase2", &fHslider108, 0.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("rotphase3", &fHslider106, 0.0, 0.0, 1.0, 0.01);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Global_Parameters");
		ui_interface->declare(&fHslider36, "7", "");
		ui_interface->addHorizontalSlider("dStretch", &fHslider36, 1.0, 0.01, 10.0, 0.01);
		ui_interface->declare(&fHslider35, "7", "");
		ui_interface->addHorizontalSlider("delharmoGain", &fHslider35, 0.0, -127.0, 18.0, 0.01);
		ui_interface->declare(&fHslider0, "7", "");
		ui_interface->addHorizontalSlider("generalGain", &fHslider0, 0.0, -127.0, 18.0, 0.01);
		ui_interface->declare(&fHslider101, "7", "");
		ui_interface->addHorizontalSlider("guitarGain", &fHslider101, -34.0, -127.0, 18.0, 0.01);
		ui_interface->declare(&fHslider38, "7", "");
		ui_interface->addHorizontalSlider("hStretch", &fHslider38, 1.0, -10.0, 10.0, 0.01);
		ui_interface->addHorizontalSlider("hWin", &fHslider40, 64.0, 1.0, 127.0, 0.01);
		ui_interface->addHorizontalSlider("smoothDuration", &fHslider1, 20.0, 10.0, 5000.0, 1.0);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Lines");
		ui_interface->openVerticalBox("Del_Durations");
		ui_interface->addHorizontalSlider("d 0", &fHslider37, 100.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 1", &fHslider42, 200.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 2", &fHslider45, 300.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 3", &fHslider48, 400.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 4", &fHslider51, 500.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 5", &fHslider54, 600.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 6", &fHslider57, 700.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 7", &fHslider60, 800.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 8", &fHslider63, 900.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d 9", &fHslider66, 1000.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d10", &fHslider69, 1100.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d11", &fHslider72, 1200.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d12", &fHslider75, 1300.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d13", &fHslider78, 1400.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d14", &fHslider81, 1500.0, 0.0, 21000.0, 1.0);
		ui_interface->addHorizontalSlider("d15", &fHslider84, 1600.0, 0.0, 21000.0, 1.0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del_Feedbacks");
		ui_interface->addHorizontalSlider("fd 0", &fHslider3, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 1", &fHslider5, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 2", &fHslider7, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 3", &fHslider9, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 4", &fHslider11, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 5", &fHslider13, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 6", &fHslider15, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 7", &fHslider17, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 8", &fHslider19, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd 9", &fHslider21, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd10", &fHslider23, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd11", &fHslider25, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd12", &fHslider27, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd13", &fHslider29, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd14", &fHslider31, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->addHorizontalSlider("fd15", &fHslider33, 0.0, 0.0, 0.98999999999999999, 0.01);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("EffeX_vs_Del");
		ui_interface->addHorizontalSlider("xvd 0", &fHslider2, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 1", &fHslider4, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 2", &fHslider6, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 3", &fHslider8, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 4", &fHslider10, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 5", &fHslider12, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 6", &fHslider14, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 7", &fHslider16, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 8", &fHslider18, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd 9", &fHslider20, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd10", &fHslider22, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd11", &fHslider24, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd12", &fHslider26, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd13", &fHslider28, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd14", &fHslider30, 1.0, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("xvd15", &fHslider32, 1.0, 0.0, 1.0, 0.01);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Harmo_Transpositions");
		ui_interface->addHorizontalSlider("tr 0", &fHslider39, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 1", &fHslider43, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 2", &fHslider46, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 3", &fHslider49, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 4", &fHslider52, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 5", &fHslider55, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 6", &fHslider58, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 7", &fHslider61, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 8", &fHslider64, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr 9", &fHslider67, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr10", &fHslider70, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr11", &fHslider73, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr12", &fHslider76, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr13", &fHslider79, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr14", &fHslider82, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->addHorizontalSlider("tr15", &fHslider85, 0.0, -2400.0, 2400.0, 1.0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Line_input");
		ui_interface->declare(&fHslider34, "5", "");
		ui_interface->addHorizontalSlider("inp 0", &fHslider34, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider41, "5", "");
		ui_interface->addHorizontalSlider("inp 1", &fHslider41, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider44, "5", "");
		ui_interface->addHorizontalSlider("inp 2", &fHslider44, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider47, "5", "");
		ui_interface->addHorizontalSlider("inp 3", &fHslider47, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider50, "5", "");
		ui_interface->addHorizontalSlider("inp 4", &fHslider50, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider53, "5", "");
		ui_interface->addHorizontalSlider("inp 5", &fHslider53, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider56, "5", "");
		ui_interface->addHorizontalSlider("inp 6", &fHslider56, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider59, "5", "");
		ui_interface->addHorizontalSlider("inp 7", &fHslider59, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider62, "5", "");
		ui_interface->addHorizontalSlider("inp 8", &fHslider62, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider65, "5", "");
		ui_interface->addHorizontalSlider("inp 9", &fHslider65, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider68, "5", "");
		ui_interface->addHorizontalSlider("inp10", &fHslider68, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider71, "5", "");
		ui_interface->addHorizontalSlider("inp11", &fHslider71, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider74, "5", "");
		ui_interface->addHorizontalSlider("inp12", &fHslider74, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider77, "5", "");
		ui_interface->addHorizontalSlider("inp13", &fHslider77, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider80, "5", "");
		ui_interface->addHorizontalSlider("inp14", &fHslider80, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider83, "5", "");
		ui_interface->addHorizontalSlider("inp15", &fHslider83, 1.0, 0.0, 1.0, 0.01);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Line_output");
		ui_interface->declare(&fHslider102, "6", "");
		ui_interface->addHorizontalSlider("out 0", &fHslider102, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider100, "6", "");
		ui_interface->addHorizontalSlider("out 1", &fHslider100, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider99, "6", "");
		ui_interface->addHorizontalSlider("out 2", &fHslider99, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider98, "6", "");
		ui_interface->addHorizontalSlider("out 3", &fHslider98, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider97, "6", "");
		ui_interface->addHorizontalSlider("out 4", &fHslider97, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider96, "6", "");
		ui_interface->addHorizontalSlider("out 5", &fHslider96, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider95, "6", "");
		ui_interface->addHorizontalSlider("out 6", &fHslider95, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider94, "6", "");
		ui_interface->addHorizontalSlider("out 7", &fHslider94, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider93, "6", "");
		ui_interface->addHorizontalSlider("out 8", &fHslider93, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider92, "6", "");
		ui_interface->addHorizontalSlider("out 9", &fHslider92, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider91, "6", "");
		ui_interface->addHorizontalSlider("out10", &fHslider91, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider90, "6", "");
		ui_interface->addHorizontalSlider("out11", &fHslider90, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider89, "6", "");
		ui_interface->addHorizontalSlider("out12", &fHslider89, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider88, "6", "");
		ui_interface->addHorizontalSlider("out13", &fHslider88, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider87, "6", "");
		ui_interface->addHorizontalSlider("out14", &fHslider87, 1.0, 0.0, 1.0, 0.01);
		ui_interface->declare(&fHslider86, "6", "");
		ui_interface->addHorizontalSlider("out15", &fHslider86, 1.0, 0.0, 1.0, 0.01);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Reinjection_Matrix");
		ui_interface->openVerticalBox("Del 0-->");
		ui_interface->addCheckButton("r  0", &fCheckbox0);
		ui_interface->addCheckButton("r 16", &fCheckbox16);
		ui_interface->addCheckButton("r 32", &fCheckbox32);
		ui_interface->addCheckButton("r 48", &fCheckbox48);
		ui_interface->addCheckButton("r 64", &fCheckbox64);
		ui_interface->addCheckButton("r 80", &fCheckbox80);
		ui_interface->addCheckButton("r 96", &fCheckbox96);
		ui_interface->addCheckButton("r112", &fCheckbox112);
		ui_interface->addCheckButton("r128", &fCheckbox128);
		ui_interface->addCheckButton("r144", &fCheckbox144);
		ui_interface->addCheckButton("r160", &fCheckbox160);
		ui_interface->addCheckButton("r176", &fCheckbox176);
		ui_interface->addCheckButton("r192", &fCheckbox192);
		ui_interface->addCheckButton("r208", &fCheckbox208);
		ui_interface->addCheckButton("r224", &fCheckbox224);
		ui_interface->addCheckButton("r240", &fCheckbox240);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 1-->");
		ui_interface->addCheckButton("r  1", &fCheckbox1);
		ui_interface->addCheckButton("r 17", &fCheckbox17);
		ui_interface->addCheckButton("r 33", &fCheckbox33);
		ui_interface->addCheckButton("r 49", &fCheckbox49);
		ui_interface->addCheckButton("r 65", &fCheckbox65);
		ui_interface->addCheckButton("r 81", &fCheckbox81);
		ui_interface->addCheckButton("r 97", &fCheckbox97);
		ui_interface->addCheckButton("r113", &fCheckbox113);
		ui_interface->addCheckButton("r129", &fCheckbox129);
		ui_interface->addCheckButton("r145", &fCheckbox145);
		ui_interface->addCheckButton("r161", &fCheckbox161);
		ui_interface->addCheckButton("r177", &fCheckbox177);
		ui_interface->addCheckButton("r193", &fCheckbox193);
		ui_interface->addCheckButton("r209", &fCheckbox209);
		ui_interface->addCheckButton("r225", &fCheckbox225);
		ui_interface->addCheckButton("r241", &fCheckbox241);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 2-->");
		ui_interface->addCheckButton("r  2", &fCheckbox2);
		ui_interface->addCheckButton("r 18", &fCheckbox18);
		ui_interface->addCheckButton("r 34", &fCheckbox34);
		ui_interface->addCheckButton("r 50", &fCheckbox50);
		ui_interface->addCheckButton("r 66", &fCheckbox66);
		ui_interface->addCheckButton("r 82", &fCheckbox82);
		ui_interface->addCheckButton("r 98", &fCheckbox98);
		ui_interface->addCheckButton("r114", &fCheckbox114);
		ui_interface->addCheckButton("r130", &fCheckbox130);
		ui_interface->addCheckButton("r146", &fCheckbox146);
		ui_interface->addCheckButton("r162", &fCheckbox162);
		ui_interface->addCheckButton("r178", &fCheckbox178);
		ui_interface->addCheckButton("r194", &fCheckbox194);
		ui_interface->addCheckButton("r210", &fCheckbox210);
		ui_interface->addCheckButton("r226", &fCheckbox226);
		ui_interface->addCheckButton("r242", &fCheckbox242);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 3-->");
		ui_interface->addCheckButton("r  3", &fCheckbox3);
		ui_interface->addCheckButton("r 19", &fCheckbox19);
		ui_interface->addCheckButton("r 35", &fCheckbox35);
		ui_interface->addCheckButton("r 51", &fCheckbox51);
		ui_interface->addCheckButton("r 67", &fCheckbox67);
		ui_interface->addCheckButton("r 83", &fCheckbox83);
		ui_interface->addCheckButton("r 99", &fCheckbox99);
		ui_interface->addCheckButton("r115", &fCheckbox115);
		ui_interface->addCheckButton("r131", &fCheckbox131);
		ui_interface->addCheckButton("r147", &fCheckbox147);
		ui_interface->addCheckButton("r163", &fCheckbox163);
		ui_interface->addCheckButton("r179", &fCheckbox179);
		ui_interface->addCheckButton("r195", &fCheckbox195);
		ui_interface->addCheckButton("r211", &fCheckbox211);
		ui_interface->addCheckButton("r227", &fCheckbox227);
		ui_interface->addCheckButton("r243", &fCheckbox243);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 4-->");
		ui_interface->addCheckButton("r  4", &fCheckbox4);
		ui_interface->addCheckButton("r 20", &fCheckbox20);
		ui_interface->addCheckButton("r 36", &fCheckbox36);
		ui_interface->addCheckButton("r 52", &fCheckbox52);
		ui_interface->addCheckButton("r 68", &fCheckbox68);
		ui_interface->addCheckButton("r 84", &fCheckbox84);
		ui_interface->addCheckButton("r100", &fCheckbox100);
		ui_interface->addCheckButton("r116", &fCheckbox116);
		ui_interface->addCheckButton("r132", &fCheckbox132);
		ui_interface->addCheckButton("r148", &fCheckbox148);
		ui_interface->addCheckButton("r164", &fCheckbox164);
		ui_interface->addCheckButton("r180", &fCheckbox180);
		ui_interface->addCheckButton("r196", &fCheckbox196);
		ui_interface->addCheckButton("r212", &fCheckbox212);
		ui_interface->addCheckButton("r228", &fCheckbox228);
		ui_interface->addCheckButton("r244", &fCheckbox244);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 5-->");
		ui_interface->addCheckButton("r  5", &fCheckbox5);
		ui_interface->addCheckButton("r 21", &fCheckbox21);
		ui_interface->addCheckButton("r 37", &fCheckbox37);
		ui_interface->addCheckButton("r 53", &fCheckbox53);
		ui_interface->addCheckButton("r 69", &fCheckbox69);
		ui_interface->addCheckButton("r 85", &fCheckbox85);
		ui_interface->addCheckButton("r101", &fCheckbox101);
		ui_interface->addCheckButton("r117", &fCheckbox117);
		ui_interface->addCheckButton("r133", &fCheckbox133);
		ui_interface->addCheckButton("r149", &fCheckbox149);
		ui_interface->addCheckButton("r165", &fCheckbox165);
		ui_interface->addCheckButton("r181", &fCheckbox181);
		ui_interface->addCheckButton("r197", &fCheckbox197);
		ui_interface->addCheckButton("r213", &fCheckbox213);
		ui_interface->addCheckButton("r229", &fCheckbox229);
		ui_interface->addCheckButton("r245", &fCheckbox245);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 6-->");
		ui_interface->addCheckButton("r  6", &fCheckbox6);
		ui_interface->addCheckButton("r 22", &fCheckbox22);
		ui_interface->addCheckButton("r 38", &fCheckbox38);
		ui_interface->addCheckButton("r 54", &fCheckbox54);
		ui_interface->addCheckButton("r 70", &fCheckbox70);
		ui_interface->addCheckButton("r 86", &fCheckbox86);
		ui_interface->addCheckButton("r102", &fCheckbox102);
		ui_interface->addCheckButton("r118", &fCheckbox118);
		ui_interface->addCheckButton("r134", &fCheckbox134);
		ui_interface->addCheckButton("r150", &fCheckbox150);
		ui_interface->addCheckButton("r166", &fCheckbox166);
		ui_interface->addCheckButton("r182", &fCheckbox182);
		ui_interface->addCheckButton("r198", &fCheckbox198);
		ui_interface->addCheckButton("r214", &fCheckbox214);
		ui_interface->addCheckButton("r230", &fCheckbox230);
		ui_interface->addCheckButton("r246", &fCheckbox246);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 7-->");
		ui_interface->addCheckButton("r  7", &fCheckbox7);
		ui_interface->addCheckButton("r 23", &fCheckbox23);
		ui_interface->addCheckButton("r 39", &fCheckbox39);
		ui_interface->addCheckButton("r 55", &fCheckbox55);
		ui_interface->addCheckButton("r 71", &fCheckbox71);
		ui_interface->addCheckButton("r 87", &fCheckbox87);
		ui_interface->addCheckButton("r103", &fCheckbox103);
		ui_interface->addCheckButton("r119", &fCheckbox119);
		ui_interface->addCheckButton("r135", &fCheckbox135);
		ui_interface->addCheckButton("r151", &fCheckbox151);
		ui_interface->addCheckButton("r167", &fCheckbox167);
		ui_interface->addCheckButton("r183", &fCheckbox183);
		ui_interface->addCheckButton("r199", &fCheckbox199);
		ui_interface->addCheckButton("r215", &fCheckbox215);
		ui_interface->addCheckButton("r231", &fCheckbox231);
		ui_interface->addCheckButton("r247", &fCheckbox247);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 8-->");
		ui_interface->addCheckButton("r  8", &fCheckbox8);
		ui_interface->addCheckButton("r 24", &fCheckbox24);
		ui_interface->addCheckButton("r 40", &fCheckbox40);
		ui_interface->addCheckButton("r 56", &fCheckbox56);
		ui_interface->addCheckButton("r 72", &fCheckbox72);
		ui_interface->addCheckButton("r 88", &fCheckbox88);
		ui_interface->addCheckButton("r104", &fCheckbox104);
		ui_interface->addCheckButton("r120", &fCheckbox120);
		ui_interface->addCheckButton("r136", &fCheckbox136);
		ui_interface->addCheckButton("r152", &fCheckbox152);
		ui_interface->addCheckButton("r168", &fCheckbox168);
		ui_interface->addCheckButton("r184", &fCheckbox184);
		ui_interface->addCheckButton("r200", &fCheckbox200);
		ui_interface->addCheckButton("r216", &fCheckbox216);
		ui_interface->addCheckButton("r232", &fCheckbox232);
		ui_interface->addCheckButton("r248", &fCheckbox248);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del 9-->");
		ui_interface->addCheckButton("r  9", &fCheckbox9);
		ui_interface->addCheckButton("r 25", &fCheckbox25);
		ui_interface->addCheckButton("r 41", &fCheckbox41);
		ui_interface->addCheckButton("r 57", &fCheckbox57);
		ui_interface->addCheckButton("r 73", &fCheckbox73);
		ui_interface->addCheckButton("r 89", &fCheckbox89);
		ui_interface->addCheckButton("r105", &fCheckbox105);
		ui_interface->addCheckButton("r121", &fCheckbox121);
		ui_interface->addCheckButton("r137", &fCheckbox137);
		ui_interface->addCheckButton("r153", &fCheckbox153);
		ui_interface->addCheckButton("r169", &fCheckbox169);
		ui_interface->addCheckButton("r185", &fCheckbox185);
		ui_interface->addCheckButton("r201", &fCheckbox201);
		ui_interface->addCheckButton("r217", &fCheckbox217);
		ui_interface->addCheckButton("r233", &fCheckbox233);
		ui_interface->addCheckButton("r249", &fCheckbox249);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del10-->");
		ui_interface->addCheckButton("r 10", &fCheckbox10);
		ui_interface->addCheckButton("r 26", &fCheckbox26);
		ui_interface->addCheckButton("r 42", &fCheckbox42);
		ui_interface->addCheckButton("r 58", &fCheckbox58);
		ui_interface->addCheckButton("r 74", &fCheckbox74);
		ui_interface->addCheckButton("r 90", &fCheckbox90);
		ui_interface->addCheckButton("r106", &fCheckbox106);
		ui_interface->addCheckButton("r122", &fCheckbox122);
		ui_interface->addCheckButton("r138", &fCheckbox138);
		ui_interface->addCheckButton("r154", &fCheckbox154);
		ui_interface->addCheckButton("r170", &fCheckbox170);
		ui_interface->addCheckButton("r186", &fCheckbox186);
		ui_interface->addCheckButton("r202", &fCheckbox202);
		ui_interface->addCheckButton("r218", &fCheckbox218);
		ui_interface->addCheckButton("r234", &fCheckbox234);
		ui_interface->addCheckButton("r250", &fCheckbox250);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del11-->");
		ui_interface->addCheckButton("r 11", &fCheckbox11);
		ui_interface->addCheckButton("r 27", &fCheckbox27);
		ui_interface->addCheckButton("r 43", &fCheckbox43);
		ui_interface->addCheckButton("r 59", &fCheckbox59);
		ui_interface->addCheckButton("r 75", &fCheckbox75);
		ui_interface->addCheckButton("r 91", &fCheckbox91);
		ui_interface->addCheckButton("r107", &fCheckbox107);
		ui_interface->addCheckButton("r123", &fCheckbox123);
		ui_interface->addCheckButton("r139", &fCheckbox139);
		ui_interface->addCheckButton("r155", &fCheckbox155);
		ui_interface->addCheckButton("r171", &fCheckbox171);
		ui_interface->addCheckButton("r187", &fCheckbox187);
		ui_interface->addCheckButton("r203", &fCheckbox203);
		ui_interface->addCheckButton("r219", &fCheckbox219);
		ui_interface->addCheckButton("r235", &fCheckbox235);
		ui_interface->addCheckButton("r251", &fCheckbox251);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del12-->");
		ui_interface->addCheckButton("r 12", &fCheckbox12);
		ui_interface->addCheckButton("r 28", &fCheckbox28);
		ui_interface->addCheckButton("r 44", &fCheckbox44);
		ui_interface->addCheckButton("r 60", &fCheckbox60);
		ui_interface->addCheckButton("r 76", &fCheckbox76);
		ui_interface->addCheckButton("r 92", &fCheckbox92);
		ui_interface->addCheckButton("r108", &fCheckbox108);
		ui_interface->addCheckButton("r124", &fCheckbox124);
		ui_interface->addCheckButton("r140", &fCheckbox140);
		ui_interface->addCheckButton("r156", &fCheckbox156);
		ui_interface->addCheckButton("r172", &fCheckbox172);
		ui_interface->addCheckButton("r188", &fCheckbox188);
		ui_interface->addCheckButton("r204", &fCheckbox204);
		ui_interface->addCheckButton("r220", &fCheckbox220);
		ui_interface->addCheckButton("r236", &fCheckbox236);
		ui_interface->addCheckButton("r252", &fCheckbox252);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del13-->");
		ui_interface->addCheckButton("r 13", &fCheckbox13);
		ui_interface->addCheckButton("r 29", &fCheckbox29);
		ui_interface->addCheckButton("r 45", &fCheckbox45);
		ui_interface->addCheckButton("r 61", &fCheckbox61);
		ui_interface->addCheckButton("r 77", &fCheckbox77);
		ui_interface->addCheckButton("r 93", &fCheckbox93);
		ui_interface->addCheckButton("r109", &fCheckbox109);
		ui_interface->addCheckButton("r125", &fCheckbox125);
		ui_interface->addCheckButton("r141", &fCheckbox141);
		ui_interface->addCheckButton("r157", &fCheckbox157);
		ui_interface->addCheckButton("r173", &fCheckbox173);
		ui_interface->addCheckButton("r189", &fCheckbox189);
		ui_interface->addCheckButton("r205", &fCheckbox205);
		ui_interface->addCheckButton("r221", &fCheckbox221);
		ui_interface->addCheckButton("r237", &fCheckbox237);
		ui_interface->addCheckButton("r253", &fCheckbox253);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del14-->");
		ui_interface->addCheckButton("r 14", &fCheckbox14);
		ui_interface->addCheckButton("r 30", &fCheckbox30);
		ui_interface->addCheckButton("r 46", &fCheckbox46);
		ui_interface->addCheckButton("r 62", &fCheckbox62);
		ui_interface->addCheckButton("r 78", &fCheckbox78);
		ui_interface->addCheckButton("r 94", &fCheckbox94);
		ui_interface->addCheckButton("r110", &fCheckbox110);
		ui_interface->addCheckButton("r126", &fCheckbox126);
		ui_interface->addCheckButton("r142", &fCheckbox142);
		ui_interface->addCheckButton("r158", &fCheckbox158);
		ui_interface->addCheckButton("r174", &fCheckbox174);
		ui_interface->addCheckButton("r190", &fCheckbox190);
		ui_interface->addCheckButton("r206", &fCheckbox206);
		ui_interface->addCheckButton("r222", &fCheckbox222);
		ui_interface->addCheckButton("r238", &fCheckbox238);
		ui_interface->addCheckButton("r254", &fCheckbox254);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Del15-->");
		ui_interface->addCheckButton("r 15", &fCheckbox15);
		ui_interface->addCheckButton("r 31", &fCheckbox31);
		ui_interface->addCheckButton("r 47", &fCheckbox47);
		ui_interface->addCheckButton("r 63", &fCheckbox63);
		ui_interface->addCheckButton("r 79", &fCheckbox79);
		ui_interface->addCheckButton("r 95", &fCheckbox95);
		ui_interface->addCheckButton("r111", &fCheckbox111);
		ui_interface->addCheckButton("r127", &fCheckbox127);
		ui_interface->addCheckButton("r143", &fCheckbox143);
		ui_interface->addCheckButton("r159", &fCheckbox159);
		ui_interface->addCheckButton("r175", &fCheckbox175);
		ui_interface->addCheckButton("r191", &fCheckbox191);
		ui_interface->addCheckButton("r207", &fCheckbox207);
		ui_interface->addCheckButton("r223", &fCheckbox223);
		ui_interface->addCheckButton("r239", &fCheckbox239);
		ui_interface->addCheckButton("r255", &fCheckbox255);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("SpatializationMatrix");
		ui_interface->openVerticalBox("Sig 0-->");
		ui_interface->addCheckButton("sp  0", &fCheckbox336);
		ui_interface->addCheckButton("sp 17", &fCheckbox342);
		ui_interface->addCheckButton("sp 34", &fCheckbox359);
		ui_interface->addCheckButton("sp 51", &fCheckbox376);
		ui_interface->addCheckButton("sp 68", &fCheckbox393);
		ui_interface->addCheckButton("sp 85", &fCheckbox410);
		ui_interface->addCheckButton("sp102", &fCheckbox427);
		ui_interface->addCheckButton("sp119", &fCheckbox339);
		ui_interface->addCheckButton("sp136", &fCheckbox340);
		ui_interface->addCheckButton("sp153", &fCheckbox338);
		ui_interface->addCheckButton("sp170", &fCheckbox337);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 1-->");
		ui_interface->addCheckButton("sp  1", &fCheckbox326);
		ui_interface->addCheckButton("sp 18", &fCheckbox343);
		ui_interface->addCheckButton("sp 35", &fCheckbox360);
		ui_interface->addCheckButton("sp 52", &fCheckbox377);
		ui_interface->addCheckButton("sp 69", &fCheckbox394);
		ui_interface->addCheckButton("sp 86", &fCheckbox411);
		ui_interface->addCheckButton("sp103", &fCheckbox428);
		ui_interface->addCheckButton("sp120", &fCheckbox329);
		ui_interface->addCheckButton("sp137", &fCheckbox330);
		ui_interface->addCheckButton("sp154", &fCheckbox328);
		ui_interface->addCheckButton("sp171", &fCheckbox327);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 2-->");
		ui_interface->addCheckButton("sp  2", &fCheckbox321);
		ui_interface->addCheckButton("sp 19", &fCheckbox344);
		ui_interface->addCheckButton("sp 36", &fCheckbox361);
		ui_interface->addCheckButton("sp 53", &fCheckbox378);
		ui_interface->addCheckButton("sp 70", &fCheckbox395);
		ui_interface->addCheckButton("sp 87", &fCheckbox412);
		ui_interface->addCheckButton("sp104", &fCheckbox429);
		ui_interface->addCheckButton("sp121", &fCheckbox324);
		ui_interface->addCheckButton("sp138", &fCheckbox325);
		ui_interface->addCheckButton("sp155", &fCheckbox323);
		ui_interface->addCheckButton("sp172", &fCheckbox322);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 3-->");
		ui_interface->addCheckButton("sp  3", &fCheckbox316);
		ui_interface->addCheckButton("sp 20", &fCheckbox345);
		ui_interface->addCheckButton("sp 37", &fCheckbox362);
		ui_interface->addCheckButton("sp 54", &fCheckbox379);
		ui_interface->addCheckButton("sp 71", &fCheckbox396);
		ui_interface->addCheckButton("sp 88", &fCheckbox413);
		ui_interface->addCheckButton("sp105", &fCheckbox430);
		ui_interface->addCheckButton("sp122", &fCheckbox319);
		ui_interface->addCheckButton("sp139", &fCheckbox320);
		ui_interface->addCheckButton("sp156", &fCheckbox318);
		ui_interface->addCheckButton("sp173", &fCheckbox317);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 4-->");
		ui_interface->addCheckButton("sp  4", &fCheckbox311);
		ui_interface->addCheckButton("sp 21", &fCheckbox346);
		ui_interface->addCheckButton("sp 38", &fCheckbox363);
		ui_interface->addCheckButton("sp 55", &fCheckbox380);
		ui_interface->addCheckButton("sp 72", &fCheckbox397);
		ui_interface->addCheckButton("sp 89", &fCheckbox414);
		ui_interface->addCheckButton("sp106", &fCheckbox431);
		ui_interface->addCheckButton("sp123", &fCheckbox314);
		ui_interface->addCheckButton("sp140", &fCheckbox315);
		ui_interface->addCheckButton("sp157", &fCheckbox313);
		ui_interface->addCheckButton("sp174", &fCheckbox312);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 5-->");
		ui_interface->addCheckButton("sp  5", &fCheckbox306);
		ui_interface->addCheckButton("sp 22", &fCheckbox347);
		ui_interface->addCheckButton("sp 39", &fCheckbox364);
		ui_interface->addCheckButton("sp 56", &fCheckbox381);
		ui_interface->addCheckButton("sp 73", &fCheckbox398);
		ui_interface->addCheckButton("sp 90", &fCheckbox415);
		ui_interface->addCheckButton("sp107", &fCheckbox432);
		ui_interface->addCheckButton("sp124", &fCheckbox309);
		ui_interface->addCheckButton("sp141", &fCheckbox310);
		ui_interface->addCheckButton("sp158", &fCheckbox308);
		ui_interface->addCheckButton("sp175", &fCheckbox307);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 6-->");
		ui_interface->addCheckButton("sp  6", &fCheckbox301);
		ui_interface->addCheckButton("sp 23", &fCheckbox348);
		ui_interface->addCheckButton("sp 40", &fCheckbox365);
		ui_interface->addCheckButton("sp 57", &fCheckbox382);
		ui_interface->addCheckButton("sp 74", &fCheckbox399);
		ui_interface->addCheckButton("sp 91", &fCheckbox416);
		ui_interface->addCheckButton("sp108", &fCheckbox433);
		ui_interface->addCheckButton("sp125", &fCheckbox304);
		ui_interface->addCheckButton("sp142", &fCheckbox305);
		ui_interface->addCheckButton("sp159", &fCheckbox303);
		ui_interface->addCheckButton("sp176", &fCheckbox302);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 7-->");
		ui_interface->addCheckButton("sp  7", &fCheckbox296);
		ui_interface->addCheckButton("sp 24", &fCheckbox349);
		ui_interface->addCheckButton("sp 41", &fCheckbox366);
		ui_interface->addCheckButton("sp 58", &fCheckbox383);
		ui_interface->addCheckButton("sp 75", &fCheckbox400);
		ui_interface->addCheckButton("sp 92", &fCheckbox417);
		ui_interface->addCheckButton("sp109", &fCheckbox434);
		ui_interface->addCheckButton("sp126", &fCheckbox299);
		ui_interface->addCheckButton("sp143", &fCheckbox300);
		ui_interface->addCheckButton("sp160", &fCheckbox298);
		ui_interface->addCheckButton("sp177", &fCheckbox297);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 8-->");
		ui_interface->addCheckButton("sp  8", &fCheckbox291);
		ui_interface->addCheckButton("sp 25", &fCheckbox350);
		ui_interface->addCheckButton("sp 42", &fCheckbox367);
		ui_interface->addCheckButton("sp 59", &fCheckbox384);
		ui_interface->addCheckButton("sp 76", &fCheckbox401);
		ui_interface->addCheckButton("sp 93", &fCheckbox418);
		ui_interface->addCheckButton("sp110", &fCheckbox435);
		ui_interface->addCheckButton("sp127", &fCheckbox294);
		ui_interface->addCheckButton("sp144", &fCheckbox295);
		ui_interface->addCheckButton("sp161", &fCheckbox293);
		ui_interface->addCheckButton("sp178", &fCheckbox292);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig 9-->");
		ui_interface->addCheckButton("sp  9", &fCheckbox286);
		ui_interface->addCheckButton("sp 26", &fCheckbox351);
		ui_interface->addCheckButton("sp 43", &fCheckbox368);
		ui_interface->addCheckButton("sp 60", &fCheckbox385);
		ui_interface->addCheckButton("sp 77", &fCheckbox402);
		ui_interface->addCheckButton("sp 94", &fCheckbox419);
		ui_interface->addCheckButton("sp111", &fCheckbox436);
		ui_interface->addCheckButton("sp128", &fCheckbox289);
		ui_interface->addCheckButton("sp145", &fCheckbox290);
		ui_interface->addCheckButton("sp162", &fCheckbox288);
		ui_interface->addCheckButton("sp179", &fCheckbox287);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig10-->");
		ui_interface->addCheckButton("sp 10", &fCheckbox281);
		ui_interface->addCheckButton("sp 27", &fCheckbox352);
		ui_interface->addCheckButton("sp 44", &fCheckbox369);
		ui_interface->addCheckButton("sp 61", &fCheckbox386);
		ui_interface->addCheckButton("sp 78", &fCheckbox403);
		ui_interface->addCheckButton("sp 95", &fCheckbox420);
		ui_interface->addCheckButton("sp112", &fCheckbox437);
		ui_interface->addCheckButton("sp129", &fCheckbox284);
		ui_interface->addCheckButton("sp146", &fCheckbox285);
		ui_interface->addCheckButton("sp163", &fCheckbox283);
		ui_interface->addCheckButton("sp180", &fCheckbox282);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig11-->");
		ui_interface->addCheckButton("sp 11", &fCheckbox276);
		ui_interface->addCheckButton("sp 28", &fCheckbox353);
		ui_interface->addCheckButton("sp 45", &fCheckbox370);
		ui_interface->addCheckButton("sp 62", &fCheckbox387);
		ui_interface->addCheckButton("sp 79", &fCheckbox404);
		ui_interface->addCheckButton("sp 96", &fCheckbox421);
		ui_interface->addCheckButton("sp113", &fCheckbox438);
		ui_interface->addCheckButton("sp130", &fCheckbox279);
		ui_interface->addCheckButton("sp147", &fCheckbox280);
		ui_interface->addCheckButton("sp164", &fCheckbox278);
		ui_interface->addCheckButton("sp181", &fCheckbox277);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig12-->");
		ui_interface->addCheckButton("sp 12", &fCheckbox271);
		ui_interface->addCheckButton("sp 29", &fCheckbox354);
		ui_interface->addCheckButton("sp 46", &fCheckbox371);
		ui_interface->addCheckButton("sp 63", &fCheckbox388);
		ui_interface->addCheckButton("sp 80", &fCheckbox405);
		ui_interface->addCheckButton("sp 97", &fCheckbox422);
		ui_interface->addCheckButton("sp114", &fCheckbox439);
		ui_interface->addCheckButton("sp131", &fCheckbox274);
		ui_interface->addCheckButton("sp148", &fCheckbox275);
		ui_interface->addCheckButton("sp165", &fCheckbox273);
		ui_interface->addCheckButton("sp182", &fCheckbox272);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig13-->");
		ui_interface->addCheckButton("sp 13", &fCheckbox266);
		ui_interface->addCheckButton("sp 30", &fCheckbox355);
		ui_interface->addCheckButton("sp 47", &fCheckbox372);
		ui_interface->addCheckButton("sp 64", &fCheckbox389);
		ui_interface->addCheckButton("sp 81", &fCheckbox406);
		ui_interface->addCheckButton("sp 98", &fCheckbox423);
		ui_interface->addCheckButton("sp115", &fCheckbox440);
		ui_interface->addCheckButton("sp132", &fCheckbox269);
		ui_interface->addCheckButton("sp149", &fCheckbox270);
		ui_interface->addCheckButton("sp166", &fCheckbox268);
		ui_interface->addCheckButton("sp183", &fCheckbox267);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig14-->");
		ui_interface->addCheckButton("sp 14", &fCheckbox261);
		ui_interface->addCheckButton("sp 31", &fCheckbox356);
		ui_interface->addCheckButton("sp 48", &fCheckbox373);
		ui_interface->addCheckButton("sp 65", &fCheckbox390);
		ui_interface->addCheckButton("sp 82", &fCheckbox407);
		ui_interface->addCheckButton("sp 99", &fCheckbox424);
		ui_interface->addCheckButton("sp116", &fCheckbox441);
		ui_interface->addCheckButton("sp133", &fCheckbox264);
		ui_interface->addCheckButton("sp150", &fCheckbox265);
		ui_interface->addCheckButton("sp167", &fCheckbox263);
		ui_interface->addCheckButton("sp184", &fCheckbox262);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig15-->");
		ui_interface->addCheckButton("sp 15", &fCheckbox256);
		ui_interface->addCheckButton("sp 32", &fCheckbox357);
		ui_interface->addCheckButton("sp 49", &fCheckbox374);
		ui_interface->addCheckButton("sp 66", &fCheckbox391);
		ui_interface->addCheckButton("sp 83", &fCheckbox408);
		ui_interface->addCheckButton("sp100", &fCheckbox425);
		ui_interface->addCheckButton("sp117", &fCheckbox442);
		ui_interface->addCheckButton("sp134", &fCheckbox259);
		ui_interface->addCheckButton("sp151", &fCheckbox260);
		ui_interface->addCheckButton("sp168", &fCheckbox258);
		ui_interface->addCheckButton("sp185", &fCheckbox257);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Sig16-->");
		ui_interface->addCheckButton("sp 16", &fCheckbox331);
		ui_interface->addCheckButton("sp 33", &fCheckbox341);
		ui_interface->addCheckButton("sp 50", &fCheckbox358);
		ui_interface->addCheckButton("sp 67", &fCheckbox375);
		ui_interface->addCheckButton("sp 84", &fCheckbox392);
		ui_interface->addCheckButton("sp101", &fCheckbox409);
		ui_interface->addCheckButton("sp118", &fCheckbox426);
		ui_interface->addCheckButton("sp135", &fCheckbox334);
		ui_interface->addCheckButton("sp152", &fCheckbox335);
		ui_interface->addCheckButton("sp169", &fCheckbox333);
		ui_interface->addCheckButton("sp186", &fCheckbox332);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("RandomEnv");
		ui_interface->addNumEntry("renv_freq", &fEntry0, 10.0, 0.01, 100.0, 0.01);
		ui_interface->addHorizontalSlider("renv_short", &fHslider105, 0.5, 0.0, 1.0, 0.01);
		ui_interface->addHorizontalSlider("renv_trim", &fHslider104, 0.0, -127.0, 18.0, 0.01);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider103, "unit", "deg");
		ui_interface->addHorizontalSlider("a 0", &fHslider103, 0.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider115, "unit", "deg");
		ui_interface->addHorizontalSlider("a 1", &fHslider115, 45.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider116, "unit", "deg");
		ui_interface->addHorizontalSlider("a 2", &fHslider116, 90.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider117, "unit", "deg");
		ui_interface->addHorizontalSlider("a 3", &fHslider117, 135.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider118, "unit", "deg");
		ui_interface->addHorizontalSlider("a 4", &fHslider118, 180.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider119, "unit", "deg");
		ui_interface->addHorizontalSlider("a 5", &fHslider119, 225.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider120, "unit", "deg");
		ui_interface->addHorizontalSlider("a 6", &fHslider120, 270.0, -360.0, 360.0, 1.0);
		ui_interface->declare(&fHslider121, "unit", "deg");
		ui_interface->addHorizontalSlider("a 7", &fHslider121, 315.0, -360.0, 360.0, 1.0);
		ui_interface->openVerticalBox("chopan");
		ui_interface->declare(&fHslider114, "unit", "deg");
		ui_interface->addHorizontalSlider("phi0", &fHslider114, 30.0, 1.0, 90.0, 1.0);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		double fSlow0 = std::exp((0.0 - (fConst1 / double(fHslider1))));
		double fSlow1 = (1.0 - fSlow0);
		double fSlow2 = (double(fHslider0) * fSlow1);
		double fSlow3 = double(fHslider2);
		double fSlow4 = (1.0 - (0.75 * fSlow3));
		double fSlow5 = (double(fCheckbox0) * fSlow4);
		double fSlow6 = (double(fHslider3) * fSlow1);
		double fSlow7 = double(fHslider4);
		double fSlow8 = (1.0 - (0.75 * fSlow7));
		double fSlow9 = (double(fCheckbox1) * fSlow8);
		double fSlow10 = (double(fHslider5) * fSlow1);
		double fSlow11 = double(fHslider6);
		double fSlow12 = (1.0 - (0.75 * fSlow11));
		double fSlow13 = (double(fCheckbox2) * fSlow12);
		double fSlow14 = (double(fHslider7) * fSlow1);
		double fSlow15 = double(fHslider8);
		double fSlow16 = (1.0 - (0.75 * fSlow15));
		double fSlow17 = (double(fCheckbox3) * fSlow16);
		double fSlow18 = (double(fHslider9) * fSlow1);
		double fSlow19 = double(fHslider10);
		double fSlow20 = (1.0 - (0.75 * fSlow19));
		double fSlow21 = (double(fCheckbox4) * fSlow20);
		double fSlow22 = (double(fHslider11) * fSlow1);
		double fSlow23 = double(fHslider12);
		double fSlow24 = (1.0 - (0.75 * fSlow23));
		double fSlow25 = (double(fCheckbox5) * fSlow24);
		double fSlow26 = (double(fHslider13) * fSlow1);
		double fSlow27 = double(fHslider14);
		double fSlow28 = (1.0 - (0.75 * fSlow27));
		double fSlow29 = (double(fCheckbox6) * fSlow28);
		double fSlow30 = (double(fHslider15) * fSlow1);
		double fSlow31 = double(fHslider16);
		double fSlow32 = (1.0 - (0.75 * fSlow31));
		double fSlow33 = (double(fCheckbox7) * fSlow32);
		double fSlow34 = (double(fHslider17) * fSlow1);
		double fSlow35 = double(fHslider18);
		double fSlow36 = (1.0 - (0.75 * fSlow35));
		double fSlow37 = (double(fCheckbox8) * fSlow36);
		double fSlow38 = (double(fHslider19) * fSlow1);
		double fSlow39 = double(fHslider20);
		double fSlow40 = (1.0 - (0.75 * fSlow39));
		double fSlow41 = (double(fCheckbox9) * fSlow40);
		double fSlow42 = (double(fHslider21) * fSlow1);
		double fSlow43 = double(fHslider22);
		double fSlow44 = (1.0 - (0.75 * fSlow43));
		double fSlow45 = (double(fCheckbox10) * fSlow44);
		double fSlow46 = (double(fHslider23) * fSlow1);
		double fSlow47 = double(fHslider24);
		double fSlow48 = (1.0 - (0.75 * fSlow47));
		double fSlow49 = (double(fCheckbox11) * fSlow48);
		double fSlow50 = (double(fHslider25) * fSlow1);
		double fSlow51 = double(fHslider26);
		double fSlow52 = (1.0 - (0.75 * fSlow51));
		double fSlow53 = (double(fCheckbox12) * fSlow52);
		double fSlow54 = (double(fHslider27) * fSlow1);
		double fSlow55 = double(fHslider28);
		double fSlow56 = (1.0 - (0.75 * fSlow55));
		double fSlow57 = (double(fCheckbox13) * fSlow56);
		double fSlow58 = (double(fHslider29) * fSlow1);
		double fSlow59 = double(fHslider30);
		double fSlow60 = (1.0 - (0.75 * fSlow59));
		double fSlow61 = (double(fCheckbox14) * fSlow60);
		double fSlow62 = (double(fHslider31) * fSlow1);
		double fSlow63 = double(fHslider32);
		double fSlow64 = (1.0 - (0.75 * fSlow63));
		double fSlow65 = (double(fCheckbox15) * fSlow64);
		double fSlow66 = (double(fHslider33) * fSlow1);
		double fSlow67 = (double(fHslider34) * fSlow1);
		double fSlow68 = (double(fHslider35) * fSlow1);
		double fSlow69 = double(fHslider36);
		int iSlow70 = int((fConst3 * (fSlow69 * double(fHslider37))));
		double fSlow71 = double(fHslider38);
		double fSlow72 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider39)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow73 = double(fHslider40);
		double fSlow74 = ((fSlow73 < 127.0) ? fSlow73 : 127.0);
		double fSlow75 = ((fSlow74 < 1.0) ? 0.0 : (4096.0 * std::pow(1.0717699999999999, (fSlow74 + -127.0))));
		double fSlow76 = (1.0 - fSlow3);
		double fSlow77 = (double(fCheckbox16) * fSlow4);
		double fSlow78 = (double(fCheckbox17) * fSlow8);
		double fSlow79 = (double(fCheckbox18) * fSlow12);
		double fSlow80 = (double(fCheckbox19) * fSlow16);
		double fSlow81 = (double(fCheckbox20) * fSlow20);
		double fSlow82 = (double(fCheckbox21) * fSlow24);
		double fSlow83 = (double(fCheckbox22) * fSlow28);
		double fSlow84 = (double(fCheckbox23) * fSlow32);
		double fSlow85 = (double(fCheckbox24) * fSlow36);
		double fSlow86 = (double(fCheckbox25) * fSlow40);
		double fSlow87 = (double(fCheckbox26) * fSlow44);
		double fSlow88 = (double(fCheckbox27) * fSlow48);
		double fSlow89 = (double(fCheckbox28) * fSlow52);
		double fSlow90 = (double(fCheckbox29) * fSlow56);
		double fSlow91 = (double(fCheckbox30) * fSlow60);
		double fSlow92 = (double(fCheckbox31) * fSlow64);
		double fSlow93 = (double(fHslider41) * fSlow1);
		int iSlow94 = int((fConst3 * (fSlow69 * double(fHslider42))));
		double fSlow95 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider43)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow96 = (1.0 - fSlow7);
		double fSlow97 = (double(fCheckbox32) * fSlow4);
		double fSlow98 = (double(fCheckbox33) * fSlow8);
		double fSlow99 = (double(fCheckbox34) * fSlow12);
		double fSlow100 = (double(fCheckbox35) * fSlow16);
		double fSlow101 = (double(fCheckbox36) * fSlow20);
		double fSlow102 = (double(fCheckbox37) * fSlow24);
		double fSlow103 = (double(fCheckbox38) * fSlow28);
		double fSlow104 = (double(fCheckbox39) * fSlow32);
		double fSlow105 = (double(fCheckbox40) * fSlow36);
		double fSlow106 = (double(fCheckbox41) * fSlow40);
		double fSlow107 = (double(fCheckbox42) * fSlow44);
		double fSlow108 = (double(fCheckbox43) * fSlow48);
		double fSlow109 = (double(fCheckbox44) * fSlow52);
		double fSlow110 = (double(fCheckbox45) * fSlow56);
		double fSlow111 = (double(fCheckbox46) * fSlow60);
		double fSlow112 = (double(fCheckbox47) * fSlow64);
		double fSlow113 = (double(fHslider44) * fSlow1);
		int iSlow114 = int((fConst3 * (fSlow69 * double(fHslider45))));
		double fSlow115 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider46)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow116 = (1.0 - fSlow11);
		double fSlow117 = (double(fCheckbox48) * fSlow4);
		double fSlow118 = (double(fCheckbox49) * fSlow8);
		double fSlow119 = (double(fCheckbox50) * fSlow12);
		double fSlow120 = (double(fCheckbox51) * fSlow16);
		double fSlow121 = (double(fCheckbox52) * fSlow20);
		double fSlow122 = (double(fCheckbox53) * fSlow24);
		double fSlow123 = (double(fCheckbox54) * fSlow28);
		double fSlow124 = (double(fCheckbox55) * fSlow32);
		double fSlow125 = (double(fCheckbox56) * fSlow36);
		double fSlow126 = (double(fCheckbox57) * fSlow40);
		double fSlow127 = (double(fCheckbox58) * fSlow44);
		double fSlow128 = (double(fCheckbox59) * fSlow48);
		double fSlow129 = (double(fCheckbox60) * fSlow52);
		double fSlow130 = (double(fCheckbox61) * fSlow56);
		double fSlow131 = (double(fCheckbox62) * fSlow60);
		double fSlow132 = (double(fCheckbox63) * fSlow64);
		double fSlow133 = (double(fHslider47) * fSlow1);
		int iSlow134 = int((fConst3 * (fSlow69 * double(fHslider48))));
		double fSlow135 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider49)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow136 = (1.0 - fSlow15);
		double fSlow137 = (double(fCheckbox64) * fSlow4);
		double fSlow138 = (double(fCheckbox65) * fSlow8);
		double fSlow139 = (double(fCheckbox66) * fSlow12);
		double fSlow140 = (double(fCheckbox67) * fSlow16);
		double fSlow141 = (double(fCheckbox68) * fSlow20);
		double fSlow142 = (double(fCheckbox69) * fSlow24);
		double fSlow143 = (double(fCheckbox70) * fSlow28);
		double fSlow144 = (double(fCheckbox71) * fSlow32);
		double fSlow145 = (double(fCheckbox72) * fSlow36);
		double fSlow146 = (double(fCheckbox73) * fSlow40);
		double fSlow147 = (double(fCheckbox74) * fSlow44);
		double fSlow148 = (double(fCheckbox75) * fSlow48);
		double fSlow149 = (double(fCheckbox76) * fSlow52);
		double fSlow150 = (double(fCheckbox77) * fSlow56);
		double fSlow151 = (double(fCheckbox78) * fSlow60);
		double fSlow152 = (double(fCheckbox79) * fSlow64);
		double fSlow153 = (double(fHslider50) * fSlow1);
		int iSlow154 = int((fConst3 * (fSlow69 * double(fHslider51))));
		double fSlow155 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider52)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow156 = (1.0 - fSlow19);
		double fSlow157 = (double(fCheckbox80) * fSlow4);
		double fSlow158 = (double(fCheckbox81) * fSlow8);
		double fSlow159 = (double(fCheckbox82) * fSlow12);
		double fSlow160 = (double(fCheckbox83) * fSlow16);
		double fSlow161 = (double(fCheckbox84) * fSlow20);
		double fSlow162 = (double(fCheckbox85) * fSlow24);
		double fSlow163 = (double(fCheckbox86) * fSlow28);
		double fSlow164 = (double(fCheckbox87) * fSlow32);
		double fSlow165 = (double(fCheckbox88) * fSlow36);
		double fSlow166 = (double(fCheckbox89) * fSlow40);
		double fSlow167 = (double(fCheckbox90) * fSlow44);
		double fSlow168 = (double(fCheckbox91) * fSlow48);
		double fSlow169 = (double(fCheckbox92) * fSlow52);
		double fSlow170 = (double(fCheckbox93) * fSlow56);
		double fSlow171 = (double(fCheckbox94) * fSlow60);
		double fSlow172 = (double(fCheckbox95) * fSlow64);
		double fSlow173 = (double(fHslider53) * fSlow1);
		int iSlow174 = int((fConst3 * (fSlow69 * double(fHslider54))));
		double fSlow175 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider55)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow176 = (1.0 - fSlow23);
		double fSlow177 = (double(fCheckbox96) * fSlow4);
		double fSlow178 = (double(fCheckbox97) * fSlow8);
		double fSlow179 = (double(fCheckbox98) * fSlow12);
		double fSlow180 = (double(fCheckbox99) * fSlow16);
		double fSlow181 = (double(fCheckbox100) * fSlow20);
		double fSlow182 = (double(fCheckbox101) * fSlow24);
		double fSlow183 = (double(fCheckbox102) * fSlow28);
		double fSlow184 = (double(fCheckbox103) * fSlow32);
		double fSlow185 = (double(fCheckbox104) * fSlow36);
		double fSlow186 = (double(fCheckbox105) * fSlow40);
		double fSlow187 = (double(fCheckbox106) * fSlow44);
		double fSlow188 = (double(fCheckbox107) * fSlow48);
		double fSlow189 = (double(fCheckbox108) * fSlow52);
		double fSlow190 = (double(fCheckbox109) * fSlow56);
		double fSlow191 = (double(fCheckbox110) * fSlow60);
		double fSlow192 = (double(fCheckbox111) * fSlow64);
		double fSlow193 = (double(fHslider56) * fSlow1);
		int iSlow194 = int((fConst3 * (fSlow69 * double(fHslider57))));
		double fSlow195 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider58)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow196 = (1.0 - fSlow27);
		double fSlow197 = (double(fCheckbox112) * fSlow4);
		double fSlow198 = (double(fCheckbox113) * fSlow8);
		double fSlow199 = (double(fCheckbox114) * fSlow12);
		double fSlow200 = (double(fCheckbox115) * fSlow16);
		double fSlow201 = (double(fCheckbox116) * fSlow20);
		double fSlow202 = (double(fCheckbox117) * fSlow24);
		double fSlow203 = (double(fCheckbox118) * fSlow28);
		double fSlow204 = (double(fCheckbox119) * fSlow32);
		double fSlow205 = (double(fCheckbox120) * fSlow36);
		double fSlow206 = (double(fCheckbox121) * fSlow40);
		double fSlow207 = (double(fCheckbox122) * fSlow44);
		double fSlow208 = (double(fCheckbox123) * fSlow48);
		double fSlow209 = (double(fCheckbox124) * fSlow52);
		double fSlow210 = (double(fCheckbox125) * fSlow56);
		double fSlow211 = (double(fCheckbox126) * fSlow60);
		double fSlow212 = (double(fCheckbox127) * fSlow64);
		double fSlow213 = (double(fHslider59) * fSlow1);
		int iSlow214 = int((fConst3 * (fSlow69 * double(fHslider60))));
		double fSlow215 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider61)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow216 = (1.0 - fSlow31);
		double fSlow217 = (double(fCheckbox128) * fSlow4);
		double fSlow218 = (double(fCheckbox129) * fSlow8);
		double fSlow219 = (double(fCheckbox130) * fSlow12);
		double fSlow220 = (double(fCheckbox131) * fSlow16);
		double fSlow221 = (double(fCheckbox132) * fSlow20);
		double fSlow222 = (double(fCheckbox133) * fSlow24);
		double fSlow223 = (double(fCheckbox134) * fSlow28);
		double fSlow224 = (double(fCheckbox135) * fSlow32);
		double fSlow225 = (double(fCheckbox136) * fSlow36);
		double fSlow226 = (double(fCheckbox137) * fSlow40);
		double fSlow227 = (double(fCheckbox138) * fSlow44);
		double fSlow228 = (double(fCheckbox139) * fSlow48);
		double fSlow229 = (double(fCheckbox140) * fSlow52);
		double fSlow230 = (double(fCheckbox141) * fSlow56);
		double fSlow231 = (double(fCheckbox142) * fSlow60);
		double fSlow232 = (double(fCheckbox143) * fSlow64);
		double fSlow233 = (double(fHslider62) * fSlow1);
		int iSlow234 = int((fConst3 * (fSlow69 * double(fHslider63))));
		double fSlow235 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider64)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow236 = (1.0 - fSlow35);
		double fSlow237 = (double(fCheckbox144) * fSlow4);
		double fSlow238 = (double(fCheckbox145) * fSlow8);
		double fSlow239 = (double(fCheckbox146) * fSlow12);
		double fSlow240 = (double(fCheckbox147) * fSlow16);
		double fSlow241 = (double(fCheckbox148) * fSlow20);
		double fSlow242 = (double(fCheckbox149) * fSlow24);
		double fSlow243 = (double(fCheckbox150) * fSlow28);
		double fSlow244 = (double(fCheckbox151) * fSlow32);
		double fSlow245 = (double(fCheckbox152) * fSlow36);
		double fSlow246 = (double(fCheckbox153) * fSlow40);
		double fSlow247 = (double(fCheckbox154) * fSlow44);
		double fSlow248 = (double(fCheckbox155) * fSlow48);
		double fSlow249 = (double(fCheckbox156) * fSlow52);
		double fSlow250 = (double(fCheckbox157) * fSlow56);
		double fSlow251 = (double(fCheckbox158) * fSlow60);
		double fSlow252 = (double(fCheckbox159) * fSlow64);
		double fSlow253 = (double(fHslider65) * fSlow1);
		int iSlow254 = int((fConst3 * (fSlow69 * double(fHslider66))));
		double fSlow255 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider67)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow256 = (1.0 - fSlow39);
		double fSlow257 = (double(fCheckbox160) * fSlow4);
		double fSlow258 = (double(fCheckbox161) * fSlow8);
		double fSlow259 = (double(fCheckbox162) * fSlow12);
		double fSlow260 = (double(fCheckbox163) * fSlow16);
		double fSlow261 = (double(fCheckbox164) * fSlow20);
		double fSlow262 = (double(fCheckbox165) * fSlow24);
		double fSlow263 = (double(fCheckbox166) * fSlow28);
		double fSlow264 = (double(fCheckbox167) * fSlow32);
		double fSlow265 = (double(fCheckbox168) * fSlow36);
		double fSlow266 = (double(fCheckbox169) * fSlow40);
		double fSlow267 = (double(fCheckbox170) * fSlow44);
		double fSlow268 = (double(fCheckbox171) * fSlow48);
		double fSlow269 = (double(fCheckbox172) * fSlow52);
		double fSlow270 = (double(fCheckbox173) * fSlow56);
		double fSlow271 = (double(fCheckbox174) * fSlow60);
		double fSlow272 = (double(fCheckbox175) * fSlow64);
		double fSlow273 = (double(fHslider68) * fSlow1);
		int iSlow274 = int((fConst3 * (fSlow69 * double(fHslider69))));
		double fSlow275 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider70)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow276 = (1.0 - fSlow43);
		double fSlow277 = (double(fCheckbox176) * fSlow4);
		double fSlow278 = (double(fCheckbox177) * fSlow8);
		double fSlow279 = (double(fCheckbox178) * fSlow12);
		double fSlow280 = (double(fCheckbox179) * fSlow16);
		double fSlow281 = (double(fCheckbox180) * fSlow20);
		double fSlow282 = (double(fCheckbox181) * fSlow24);
		double fSlow283 = (double(fCheckbox182) * fSlow28);
		double fSlow284 = (double(fCheckbox183) * fSlow32);
		double fSlow285 = (double(fCheckbox184) * fSlow36);
		double fSlow286 = (double(fCheckbox185) * fSlow40);
		double fSlow287 = (double(fCheckbox186) * fSlow44);
		double fSlow288 = (double(fCheckbox187) * fSlow48);
		double fSlow289 = (double(fCheckbox188) * fSlow52);
		double fSlow290 = (double(fCheckbox189) * fSlow56);
		double fSlow291 = (double(fCheckbox190) * fSlow60);
		double fSlow292 = (double(fCheckbox191) * fSlow64);
		double fSlow293 = (double(fHslider71) * fSlow1);
		int iSlow294 = int((fConst3 * (fSlow69 * double(fHslider72))));
		double fSlow295 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider73)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow296 = (1.0 - fSlow47);
		double fSlow297 = (double(fCheckbox192) * fSlow4);
		double fSlow298 = (double(fCheckbox193) * fSlow8);
		double fSlow299 = (double(fCheckbox194) * fSlow12);
		double fSlow300 = (double(fCheckbox195) * fSlow16);
		double fSlow301 = (double(fCheckbox196) * fSlow20);
		double fSlow302 = (double(fCheckbox197) * fSlow24);
		double fSlow303 = (double(fCheckbox198) * fSlow28);
		double fSlow304 = (double(fCheckbox199) * fSlow32);
		double fSlow305 = (double(fCheckbox200) * fSlow36);
		double fSlow306 = (double(fCheckbox201) * fSlow40);
		double fSlow307 = (double(fCheckbox202) * fSlow44);
		double fSlow308 = (double(fCheckbox203) * fSlow48);
		double fSlow309 = (double(fCheckbox204) * fSlow52);
		double fSlow310 = (double(fCheckbox205) * fSlow56);
		double fSlow311 = (double(fCheckbox206) * fSlow60);
		double fSlow312 = (double(fCheckbox207) * fSlow64);
		double fSlow313 = (double(fHslider74) * fSlow1);
		int iSlow314 = int((fConst3 * (fSlow69 * double(fHslider75))));
		double fSlow315 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider76)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow316 = (1.0 - fSlow51);
		double fSlow317 = (double(fCheckbox208) * fSlow4);
		double fSlow318 = (double(fCheckbox209) * fSlow8);
		double fSlow319 = (double(fCheckbox210) * fSlow12);
		double fSlow320 = (double(fCheckbox211) * fSlow16);
		double fSlow321 = (double(fCheckbox212) * fSlow20);
		double fSlow322 = (double(fCheckbox213) * fSlow24);
		double fSlow323 = (double(fCheckbox214) * fSlow28);
		double fSlow324 = (double(fCheckbox215) * fSlow32);
		double fSlow325 = (double(fCheckbox216) * fSlow36);
		double fSlow326 = (double(fCheckbox217) * fSlow40);
		double fSlow327 = (double(fCheckbox218) * fSlow44);
		double fSlow328 = (double(fCheckbox219) * fSlow48);
		double fSlow329 = (double(fCheckbox220) * fSlow52);
		double fSlow330 = (double(fCheckbox221) * fSlow56);
		double fSlow331 = (double(fCheckbox222) * fSlow60);
		double fSlow332 = (double(fCheckbox223) * fSlow64);
		double fSlow333 = (double(fHslider77) * fSlow1);
		int iSlow334 = int((fConst3 * (fSlow69 * double(fHslider78))));
		double fSlow335 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider79)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow336 = (1.0 - fSlow55);
		double fSlow337 = (double(fCheckbox224) * fSlow4);
		double fSlow338 = (double(fCheckbox225) * fSlow8);
		double fSlow339 = (double(fCheckbox226) * fSlow12);
		double fSlow340 = (double(fCheckbox227) * fSlow16);
		double fSlow341 = (double(fCheckbox228) * fSlow20);
		double fSlow342 = (double(fCheckbox229) * fSlow24);
		double fSlow343 = (double(fCheckbox230) * fSlow28);
		double fSlow344 = (double(fCheckbox231) * fSlow32);
		double fSlow345 = (double(fCheckbox232) * fSlow36);
		double fSlow346 = (double(fCheckbox233) * fSlow40);
		double fSlow347 = (double(fCheckbox234) * fSlow44);
		double fSlow348 = (double(fCheckbox235) * fSlow48);
		double fSlow349 = (double(fCheckbox236) * fSlow52);
		double fSlow350 = (double(fCheckbox237) * fSlow56);
		double fSlow351 = (double(fCheckbox238) * fSlow60);
		double fSlow352 = (double(fCheckbox239) * fSlow64);
		double fSlow353 = (double(fHslider80) * fSlow1);
		int iSlow354 = int((fConst3 * (fSlow69 * double(fHslider81))));
		double fSlow355 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider82)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow356 = (1.0 - fSlow59);
		double fSlow357 = (double(fCheckbox240) * fSlow4);
		double fSlow358 = (double(fCheckbox241) * fSlow8);
		double fSlow359 = (double(fCheckbox242) * fSlow12);
		double fSlow360 = (double(fCheckbox243) * fSlow16);
		double fSlow361 = (double(fCheckbox244) * fSlow20);
		double fSlow362 = (double(fCheckbox245) * fSlow24);
		double fSlow363 = (double(fCheckbox246) * fSlow28);
		double fSlow364 = (double(fCheckbox247) * fSlow32);
		double fSlow365 = (double(fCheckbox248) * fSlow36);
		double fSlow366 = (double(fCheckbox249) * fSlow40);
		double fSlow367 = (double(fCheckbox250) * fSlow44);
		double fSlow368 = (double(fCheckbox251) * fSlow48);
		double fSlow369 = (double(fCheckbox252) * fSlow52);
		double fSlow370 = (double(fCheckbox253) * fSlow56);
		double fSlow371 = (double(fCheckbox254) * fSlow60);
		double fSlow372 = (double(fCheckbox255) * fSlow64);
		double fSlow373 = (double(fHslider83) * fSlow1);
		int iSlow374 = int((fConst3 * (fSlow69 * double(fHslider84))));
		double fSlow375 = (fConst4 * (0.0 - (3.8224 * ((440.0 * std::pow(2.0, (0.083333333333333329 * ((0.01 * ((fSlow71 * double(fHslider85)) + 6000.0)) + -69.0)))) + -261.62597699999998))));
		double fSlow376 = (1.0 - fSlow63);
		double fSlow377 = (double(fHslider86) * fSlow1);
		double fSlow378 = (fConst7 * double(fCheckbox256));
		double fSlow379 = (fConst7 * double(fCheckbox257));
		double fSlow380 = (fConst7 * double(fCheckbox258));
		double fSlow381 = (fConst7 * double(fCheckbox259));
		double fSlow382 = (fConst7 * double(fCheckbox260));
		double fSlow383 = (double(fHslider87) * fSlow1);
		double fSlow384 = (fConst7 * double(fCheckbox261));
		double fSlow385 = (fConst7 * double(fCheckbox262));
		double fSlow386 = (fConst7 * double(fCheckbox263));
		double fSlow387 = (fConst7 * double(fCheckbox264));
		double fSlow388 = (fConst7 * double(fCheckbox265));
		double fSlow389 = (double(fHslider88) * fSlow1);
		double fSlow390 = (fConst7 * double(fCheckbox266));
		double fSlow391 = (fConst7 * double(fCheckbox267));
		double fSlow392 = (fConst7 * double(fCheckbox268));
		double fSlow393 = (fConst7 * double(fCheckbox269));
		double fSlow394 = (fConst7 * double(fCheckbox270));
		double fSlow395 = (double(fHslider89) * fSlow1);
		double fSlow396 = (fConst7 * double(fCheckbox271));
		double fSlow397 = (fConst7 * double(fCheckbox272));
		double fSlow398 = (fConst7 * double(fCheckbox273));
		double fSlow399 = (fConst7 * double(fCheckbox274));
		double fSlow400 = (fConst7 * double(fCheckbox275));
		double fSlow401 = (double(fHslider90) * fSlow1);
		double fSlow402 = (fConst7 * double(fCheckbox276));
		double fSlow403 = (fConst7 * double(fCheckbox277));
		double fSlow404 = (fConst7 * double(fCheckbox278));
		double fSlow405 = (fConst7 * double(fCheckbox279));
		double fSlow406 = (fConst7 * double(fCheckbox280));
		double fSlow407 = (double(fHslider91) * fSlow1);
		double fSlow408 = (fConst7 * double(fCheckbox281));
		double fSlow409 = (fConst7 * double(fCheckbox282));
		double fSlow410 = (fConst7 * double(fCheckbox283));
		double fSlow411 = (fConst7 * double(fCheckbox284));
		double fSlow412 = (fConst7 * double(fCheckbox285));
		double fSlow413 = (double(fHslider92) * fSlow1);
		double fSlow414 = (fConst7 * double(fCheckbox286));
		double fSlow415 = (fConst7 * double(fCheckbox287));
		double fSlow416 = (fConst7 * double(fCheckbox288));
		double fSlow417 = (fConst7 * double(fCheckbox289));
		double fSlow418 = (fConst7 * double(fCheckbox290));
		double fSlow419 = (double(fHslider93) * fSlow1);
		double fSlow420 = (fConst7 * double(fCheckbox291));
		double fSlow421 = (fConst7 * double(fCheckbox292));
		double fSlow422 = (fConst7 * double(fCheckbox293));
		double fSlow423 = (fConst7 * double(fCheckbox294));
		double fSlow424 = (fConst7 * double(fCheckbox295));
		double fSlow425 = (double(fHslider94) * fSlow1);
		double fSlow426 = (fConst7 * double(fCheckbox296));
		double fSlow427 = (fConst7 * double(fCheckbox297));
		double fSlow428 = (fConst7 * double(fCheckbox298));
		double fSlow429 = (fConst7 * double(fCheckbox299));
		double fSlow430 = (fConst7 * double(fCheckbox300));
		double fSlow431 = (double(fHslider95) * fSlow1);
		double fSlow432 = (fConst7 * double(fCheckbox301));
		double fSlow433 = (fConst7 * double(fCheckbox302));
		double fSlow434 = (fConst7 * double(fCheckbox303));
		double fSlow435 = (fConst7 * double(fCheckbox304));
		double fSlow436 = (fConst7 * double(fCheckbox305));
		double fSlow437 = (double(fHslider96) * fSlow1);
		double fSlow438 = (fConst7 * double(fCheckbox306));
		double fSlow439 = (fConst7 * double(fCheckbox307));
		double fSlow440 = (fConst7 * double(fCheckbox308));
		double fSlow441 = (fConst7 * double(fCheckbox309));
		double fSlow442 = (fConst7 * double(fCheckbox310));
		double fSlow443 = (double(fHslider97) * fSlow1);
		double fSlow444 = (fConst7 * double(fCheckbox311));
		double fSlow445 = (fConst7 * double(fCheckbox312));
		double fSlow446 = (fConst7 * double(fCheckbox313));
		double fSlow447 = (fConst7 * double(fCheckbox314));
		double fSlow448 = (fConst7 * double(fCheckbox315));
		double fSlow449 = (double(fHslider98) * fSlow1);
		double fSlow450 = (fConst7 * double(fCheckbox316));
		double fSlow451 = (fConst7 * double(fCheckbox317));
		double fSlow452 = (fConst7 * double(fCheckbox318));
		double fSlow453 = (fConst7 * double(fCheckbox319));
		double fSlow454 = (fConst7 * double(fCheckbox320));
		double fSlow455 = (double(fHslider99) * fSlow1);
		double fSlow456 = (fConst7 * double(fCheckbox321));
		double fSlow457 = (fConst7 * double(fCheckbox322));
		double fSlow458 = (fConst7 * double(fCheckbox323));
		double fSlow459 = (fConst7 * double(fCheckbox324));
		double fSlow460 = (fConst7 * double(fCheckbox325));
		double fSlow461 = (double(fHslider100) * fSlow1);
		double fSlow462 = (fConst7 * double(fCheckbox326));
		double fSlow463 = (fConst7 * double(fCheckbox327));
		double fSlow464 = (fConst7 * double(fCheckbox328));
		double fSlow465 = (fConst7 * double(fCheckbox329));
		double fSlow466 = (fConst7 * double(fCheckbox330));
		double fSlow467 = (double(fHslider101) * fSlow1);
		double fSlow468 = (fConst7 * double(fCheckbox331));
		double fSlow469 = (fConst7 * double(fCheckbox332));
		double fSlow470 = (fConst7 * double(fCheckbox333));
		double fSlow471 = (fConst7 * double(fCheckbox334));
		double fSlow472 = (fConst7 * double(fCheckbox335));
		double fSlow473 = (double(fHslider102) * fSlow1);
		double fSlow474 = (fConst7 * double(fCheckbox336));
		double fSlow475 = (fConst7 * double(fCheckbox337));
		double fSlow476 = (fConst7 * double(fCheckbox338));
		double fSlow477 = (fConst7 * double(fCheckbox339));
		double fSlow478 = (fConst7 * double(fCheckbox340));
		double fSlow479 = double(fHslider103);
		double fSlow480 = (0.017453292519943295 * fSlow479);
		double fSlow481 = (0.2857142857142857 * std::sin(fSlow480));
		double fSlow482 = (fConst7 * double(fCheckbox341));
		double fSlow483 = (double(fHslider104) * fSlow1);
		double fSlow484 = (fConst4 * double(fEntry0));
		double fSlow485 = ((2.0 * double(fHslider105)) + -1.0);
		double fSlow486 = double(fHslider106);
		double fSlow487 = double(fHslider107);
		int iSlow488 = (fSlow487 == 0.0);
		double fSlow489 = (fSlow486 * double(iSlow488));
		double fSlow490 = double((1 - iSlow488));
		double fSlow491 = (fConst4 * fSlow487);
		double fSlow492 = double(fHslider108);
		double fSlow493 = double(fHslider109);
		int iSlow494 = (fSlow493 == 0.0);
		double fSlow495 = (fSlow492 * double(iSlow494));
		double fSlow496 = double((1 - iSlow494));
		double fSlow497 = (fConst4 * fSlow493);
		double fSlow498 = double(fHslider110);
		double fSlow499 = double(fHslider111);
		int iSlow500 = (fSlow499 == 0.0);
		double fSlow501 = (fSlow498 * double(iSlow500));
		double fSlow502 = double((1 - iSlow500));
		double fSlow503 = (fConst4 * fSlow499);
		double fSlow504 = (fConst7 * double(fCheckbox342));
		double fSlow505 = (fConst7 * double(fCheckbox343));
		double fSlow506 = (fConst7 * double(fCheckbox344));
		double fSlow507 = (fConst7 * double(fCheckbox345));
		double fSlow508 = (fConst7 * double(fCheckbox346));
		double fSlow509 = (fConst7 * double(fCheckbox347));
		double fSlow510 = (fConst7 * double(fCheckbox348));
		double fSlow511 = (fConst7 * double(fCheckbox349));
		double fSlow512 = (fConst7 * double(fCheckbox350));
		double fSlow513 = (fConst7 * double(fCheckbox351));
		double fSlow514 = (fConst7 * double(fCheckbox352));
		double fSlow515 = (fConst7 * double(fCheckbox353));
		double fSlow516 = (fConst7 * double(fCheckbox354));
		double fSlow517 = (fConst7 * double(fCheckbox355));
		double fSlow518 = (fConst7 * double(fCheckbox356));
		double fSlow519 = (fConst7 * double(fCheckbox357));
		double fSlow520 = double(fHslider112);
		double fSlow521 = double(fHslider113);
		int iSlow522 = (fSlow521 == 0.0);
		double fSlow523 = (fSlow520 * double(iSlow522));
		double fSlow524 = double((1 - iSlow522));
		double fSlow525 = (fConst4 * fSlow521);
		double fSlow526 = (0.2857142857142857 * std::cos(fSlow480));
		double fSlow527 = (fConst7 * double(fCheckbox358));
		double fSlow528 = (fConst7 * double(fCheckbox359));
		double fSlow529 = (fConst7 * double(fCheckbox360));
		double fSlow530 = (fConst7 * double(fCheckbox361));
		double fSlow531 = (fConst7 * double(fCheckbox362));
		double fSlow532 = (fConst7 * double(fCheckbox363));
		double fSlow533 = (fConst7 * double(fCheckbox364));
		double fSlow534 = (fConst7 * double(fCheckbox365));
		double fSlow535 = (fConst7 * double(fCheckbox366));
		double fSlow536 = (fConst7 * double(fCheckbox367));
		double fSlow537 = (fConst7 * double(fCheckbox368));
		double fSlow538 = (fConst7 * double(fCheckbox369));
		double fSlow539 = (fConst7 * double(fCheckbox370));
		double fSlow540 = (fConst7 * double(fCheckbox371));
		double fSlow541 = (fConst7 * double(fCheckbox372));
		double fSlow542 = (fConst7 * double(fCheckbox373));
		double fSlow543 = (fConst7 * double(fCheckbox374));
		double fSlow544 = (0.034906585039886591 * fSlow479);
		double fSlow545 = (0.2857142857142857 * std::sin(fSlow544));
		double fSlow546 = (fConst7 * double(fCheckbox375));
		double fSlow547 = (fConst7 * double(fCheckbox376));
		double fSlow548 = (fConst7 * double(fCheckbox377));
		double fSlow549 = (fConst7 * double(fCheckbox378));
		double fSlow550 = (fConst7 * double(fCheckbox379));
		double fSlow551 = (fConst7 * double(fCheckbox380));
		double fSlow552 = (fConst7 * double(fCheckbox381));
		double fSlow553 = (fConst7 * double(fCheckbox382));
		double fSlow554 = (fConst7 * double(fCheckbox383));
		double fSlow555 = (fConst7 * double(fCheckbox384));
		double fSlow556 = (fConst7 * double(fCheckbox385));
		double fSlow557 = (fConst7 * double(fCheckbox386));
		double fSlow558 = (fConst7 * double(fCheckbox387));
		double fSlow559 = (fConst7 * double(fCheckbox388));
		double fSlow560 = (fConst7 * double(fCheckbox389));
		double fSlow561 = (fConst7 * double(fCheckbox390));
		double fSlow562 = (fConst7 * double(fCheckbox391));
		double fSlow563 = (0.2857142857142857 * std::cos(fSlow544));
		double fSlow564 = (fConst7 * double(fCheckbox392));
		double fSlow565 = (fConst7 * double(fCheckbox393));
		double fSlow566 = (fConst7 * double(fCheckbox394));
		double fSlow567 = (fConst7 * double(fCheckbox395));
		double fSlow568 = (fConst7 * double(fCheckbox396));
		double fSlow569 = (fConst7 * double(fCheckbox397));
		double fSlow570 = (fConst7 * double(fCheckbox398));
		double fSlow571 = (fConst7 * double(fCheckbox399));
		double fSlow572 = (fConst7 * double(fCheckbox400));
		double fSlow573 = (fConst7 * double(fCheckbox401));
		double fSlow574 = (fConst7 * double(fCheckbox402));
		double fSlow575 = (fConst7 * double(fCheckbox403));
		double fSlow576 = (fConst7 * double(fCheckbox404));
		double fSlow577 = (fConst7 * double(fCheckbox405));
		double fSlow578 = (fConst7 * double(fCheckbox406));
		double fSlow579 = (fConst7 * double(fCheckbox407));
		double fSlow580 = (fConst7 * double(fCheckbox408));
		double fSlow581 = (0.05235987755982989 * fSlow479);
		double fSlow582 = (0.2857142857142857 * std::sin(fSlow581));
		double fSlow583 = (fConst7 * double(fCheckbox409));
		double fSlow584 = (fConst7 * double(fCheckbox410));
		double fSlow585 = (fConst7 * double(fCheckbox411));
		double fSlow586 = (fConst7 * double(fCheckbox412));
		double fSlow587 = (fConst7 * double(fCheckbox413));
		double fSlow588 = (fConst7 * double(fCheckbox414));
		double fSlow589 = (fConst7 * double(fCheckbox415));
		double fSlow590 = (fConst7 * double(fCheckbox416));
		double fSlow591 = (fConst7 * double(fCheckbox417));
		double fSlow592 = (fConst7 * double(fCheckbox418));
		double fSlow593 = (fConst7 * double(fCheckbox419));
		double fSlow594 = (fConst7 * double(fCheckbox420));
		double fSlow595 = (fConst7 * double(fCheckbox421));
		double fSlow596 = (fConst7 * double(fCheckbox422));
		double fSlow597 = (fConst7 * double(fCheckbox423));
		double fSlow598 = (fConst7 * double(fCheckbox424));
		double fSlow599 = (fConst7 * double(fCheckbox425));
		double fSlow600 = (0.2857142857142857 * std::cos(fSlow581));
		double fSlow601 = (fConst7 * double(fCheckbox426));
		double fSlow602 = (fConst7 * double(fCheckbox427));
		double fSlow603 = (fConst7 * double(fCheckbox428));
		double fSlow604 = (fConst7 * double(fCheckbox429));
		double fSlow605 = (fConst7 * double(fCheckbox430));
		double fSlow606 = (fConst7 * double(fCheckbox431));
		double fSlow607 = (fConst7 * double(fCheckbox432));
		double fSlow608 = (fConst7 * double(fCheckbox433));
		double fSlow609 = (fConst7 * double(fCheckbox434));
		double fSlow610 = (fConst7 * double(fCheckbox435));
		double fSlow611 = (fConst7 * double(fCheckbox436));
		double fSlow612 = (fConst7 * double(fCheckbox437));
		double fSlow613 = (fConst7 * double(fCheckbox438));
		double fSlow614 = (fConst7 * double(fCheckbox439));
		double fSlow615 = (fConst7 * double(fCheckbox440));
		double fSlow616 = (fConst7 * double(fCheckbox441));
		double fSlow617 = (fConst7 * double(fCheckbox442));
		double fSlow618 = (0.0010000000000000009 * double(fHslider114));
		double fSlow619 = double(fHslider115);
		double fSlow620 = (0.017453292519943295 * fSlow619);
		double fSlow621 = (0.2857142857142857 * std::sin(fSlow620));
		double fSlow622 = (0.2857142857142857 * std::cos(fSlow620));
		double fSlow623 = (0.034906585039886591 * fSlow619);
		double fSlow624 = (0.2857142857142857 * std::sin(fSlow623));
		double fSlow625 = (0.2857142857142857 * std::cos(fSlow623));
		double fSlow626 = (0.05235987755982989 * fSlow619);
		double fSlow627 = (0.2857142857142857 * std::sin(fSlow626));
		double fSlow628 = (0.2857142857142857 * std::cos(fSlow626));
		double fSlow629 = double(fHslider116);
		double fSlow630 = (0.017453292519943295 * fSlow629);
		double fSlow631 = (0.2857142857142857 * std::sin(fSlow630));
		double fSlow632 = (0.2857142857142857 * std::cos(fSlow630));
		double fSlow633 = (0.034906585039886591 * fSlow629);
		double fSlow634 = (0.2857142857142857 * std::sin(fSlow633));
		double fSlow635 = (0.2857142857142857 * std::cos(fSlow633));
		double fSlow636 = (0.05235987755982989 * fSlow629);
		double fSlow637 = (0.2857142857142857 * std::sin(fSlow636));
		double fSlow638 = (0.2857142857142857 * std::cos(fSlow636));
		double fSlow639 = double(fHslider117);
		double fSlow640 = (0.017453292519943295 * fSlow639);
		double fSlow641 = (0.2857142857142857 * std::sin(fSlow640));
		double fSlow642 = (0.2857142857142857 * std::cos(fSlow640));
		double fSlow643 = (0.034906585039886591 * fSlow639);
		double fSlow644 = (0.2857142857142857 * std::sin(fSlow643));
		double fSlow645 = (0.2857142857142857 * std::cos(fSlow643));
		double fSlow646 = (0.05235987755982989 * fSlow639);
		double fSlow647 = (0.2857142857142857 * std::sin(fSlow646));
		double fSlow648 = (0.2857142857142857 * std::cos(fSlow646));
		double fSlow649 = double(fHslider118);
		double fSlow650 = (0.017453292519943295 * fSlow649);
		double fSlow651 = (0.2857142857142857 * std::sin(fSlow650));
		double fSlow652 = (0.2857142857142857 * std::cos(fSlow650));
		double fSlow653 = (0.034906585039886591 * fSlow649);
		double fSlow654 = (0.2857142857142857 * std::sin(fSlow653));
		double fSlow655 = (0.2857142857142857 * std::cos(fSlow653));
		double fSlow656 = (0.05235987755982989 * fSlow649);
		double fSlow657 = (0.2857142857142857 * std::sin(fSlow656));
		double fSlow658 = (0.2857142857142857 * std::cos(fSlow656));
		double fSlow659 = double(fHslider119);
		double fSlow660 = (0.017453292519943295 * fSlow659);
		double fSlow661 = (0.2857142857142857 * std::sin(fSlow660));
		double fSlow662 = (0.2857142857142857 * std::cos(fSlow660));
		double fSlow663 = (0.034906585039886591 * fSlow659);
		double fSlow664 = (0.2857142857142857 * std::sin(fSlow663));
		double fSlow665 = (0.2857142857142857 * std::cos(fSlow663));
		double fSlow666 = (0.05235987755982989 * fSlow659);
		double fSlow667 = (0.2857142857142857 * std::sin(fSlow666));
		double fSlow668 = (0.2857142857142857 * std::cos(fSlow666));
		double fSlow669 = double(fHslider120);
		double fSlow670 = (0.017453292519943295 * fSlow669);
		double fSlow671 = (0.2857142857142857 * std::sin(fSlow670));
		double fSlow672 = (0.2857142857142857 * std::cos(fSlow670));
		double fSlow673 = (0.034906585039886591 * fSlow669);
		double fSlow674 = (0.2857142857142857 * std::sin(fSlow673));
		double fSlow675 = (0.2857142857142857 * std::cos(fSlow673));
		double fSlow676 = (0.05235987755982989 * fSlow669);
		double fSlow677 = (0.2857142857142857 * std::sin(fSlow676));
		double fSlow678 = (0.2857142857142857 * std::cos(fSlow676));
		double fSlow679 = double(fHslider121);
		double fSlow680 = (0.017453292519943295 * fSlow679);
		double fSlow681 = (0.2857142857142857 * std::sin(fSlow680));
		double fSlow682 = (0.2857142857142857 * std::cos(fSlow680));
		double fSlow683 = (0.034906585039886591 * fSlow679);
		double fSlow684 = (0.2857142857142857 * std::sin(fSlow683));
		double fSlow685 = (0.2857142857142857 * std::cos(fSlow683));
		double fSlow686 = (0.05235987755982989 * fSlow679);
		double fSlow687 = (0.2857142857142857 * std::sin(fSlow686));
		double fSlow688 = (0.2857142857142857 * std::cos(fSlow686));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow2 + (fSlow0 * fRec0[1]));
			double fTemp0 = (double((fRec0[0] > -127.0)) * std::pow(10.0, (0.050000000000000003 * fRec0[0])));
			fRec18[0] = (fConst2 + (fRec18[1] - std::floor((fConst2 + fRec18[1]))));
			double fTemp1 = (65536.0 * (fRec18[0] - std::floor(fRec18[0])));
			int iTemp2 = int(fTemp1);
			double fTemp3 = ftbl0FilDeSoi1PanStereoSIG0[iTemp2];
			double fTemp4 = ((fTemp3 + ((fTemp1 - std::floor(fTemp1)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp2 + 1) % 65536)] - fTemp3))) + 1.0);
			fVec0[0] = fTemp4;
			fRec19[0] = (fSlow6 + (fSlow0 * fRec19[1]));
			double fTemp5 = (fRec19[0] * fRec1[1]);
			fRec20[0] = (fSlow10 + (fSlow0 * fRec20[1]));
			double fTemp6 = (fRec20[0] * fRec2[1]);
			fRec21[0] = (fSlow14 + (fSlow0 * fRec21[1]));
			double fTemp7 = (fRec21[0] * fRec3[1]);
			fRec22[0] = (fSlow18 + (fSlow0 * fRec22[1]));
			double fTemp8 = (fRec22[0] * fRec4[1]);
			fRec23[0] = (fSlow22 + (fSlow0 * fRec23[1]));
			double fTemp9 = (fRec23[0] * fRec5[1]);
			fRec24[0] = (fSlow26 + (fSlow0 * fRec24[1]));
			double fTemp10 = (fRec24[0] * fRec6[1]);
			fRec25[0] = (fSlow30 + (fSlow0 * fRec25[1]));
			double fTemp11 = (fRec25[0] * fRec7[1]);
			fRec26[0] = (fSlow34 + (fSlow0 * fRec26[1]));
			double fTemp12 = (fRec26[0] * fRec8[1]);
			fRec27[0] = (fSlow38 + (fSlow0 * fRec27[1]));
			double fTemp13 = (fRec27[0] * fRec9[1]);
			fRec28[0] = (fSlow42 + (fSlow0 * fRec28[1]));
			double fTemp14 = (fRec28[0] * fRec10[1]);
			fRec29[0] = (fSlow46 + (fSlow0 * fRec29[1]));
			double fTemp15 = (fRec29[0] * fRec11[1]);
			fRec30[0] = (fSlow50 + (fSlow0 * fRec30[1]));
			double fTemp16 = (fRec30[0] * fRec12[1]);
			fRec31[0] = (fSlow54 + (fSlow0 * fRec31[1]));
			double fTemp17 = (fRec31[0] * fRec13[1]);
			fRec32[0] = (fSlow58 + (fSlow0 * fRec32[1]));
			double fTemp18 = (fRec32[0] * fRec14[1]);
			fRec33[0] = (fSlow62 + (fSlow0 * fRec33[1]));
			double fTemp19 = (fRec33[0] * fRec15[1]);
			fRec34[0] = (fSlow66 + (fSlow0 * fRec34[1]));
			double fTemp20 = (fRec34[0] * fRec16[1]);
			double fTemp21 = double(input0[i]);
			fRec35[0] = (fSlow67 + (fSlow0 * fRec35[1]));
			fRec36[0] = (fSlow68 + (fSlow0 * fRec36[1]));
			double fTemp22 = double((fRec36[0] > -127.0));
			double fTemp23 = std::pow(10.0, (0.050000000000000003 * fRec36[0]));
			double fTemp24 = (((((((((((((((((fSlow5 * fTemp5) + (fSlow9 * fTemp6)) + (fSlow13 * fTemp7)) + (fSlow17 * fTemp8)) + (fSlow21 * fTemp9)) + (fSlow25 * fTemp10)) + (fSlow29 * fTemp11)) + (fSlow33 * fTemp12)) + (fSlow37 * fTemp13)) + (fSlow41 * fTemp14)) + (fSlow45 * fTemp15)) + (fSlow49 * fTemp16)) + (fSlow53 * fTemp17)) + (fSlow57 * fTemp18)) + (fSlow61 * fTemp19)) + (fSlow65 * fTemp20)) + (((fTemp21 * fRec35[0]) * fTemp22) * fTemp23));
			fVec1[(IOTA & 1048575)] = fTemp24;
			double fTemp25 = (0.5 * fTemp4);
			int iTemp26 = ((fTemp25 > 0.001) * ((0.5 * fVec0[1]) <= 0.001));
			int iTemp27 = (1 - iTemp26);
			iRec37[0] = ((iRec37[1] * iTemp27) + (iSlow70 * iTemp26));
			double fTemp28 = (1.0 - fTemp25);
			fVec2[0] = fTemp28;
			int iTemp29 = ((fTemp28 > 0.001) * (fVec2[1] <= 0.001));
			int iTemp30 = (1 - iTemp29);
			iRec38[0] = ((iRec38[1] * iTemp30) + (iSlow70 * iTemp29));
			double fTemp31 = ((0.5 * (fTemp4 * fVec1[((IOTA - (iRec37[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec1[((IOTA - (iRec38[0] & 1048575)) & 1048575)]));
			int iTemp32 = (fTemp31 > 1.0);
			int iTemp33 = (fTemp31 < -1.0);
			double fTemp34 = (double((iTemp32 - iTemp33)) + (fTemp31 * double(((1 - iTemp33) * (1 - iTemp32)))));
			double fTemp35 = (fSlow3 * fTemp34);
			fVec3[(IOTA & 262143)] = fTemp35;
			fVec4[0] = fSlow75;
			double fTemp36 = ((fSlow75 != fVec4[1]) ? fConst5 : (fRec41[1] + -1.0));
			fRec41[0] = fTemp36;
			fRec42[0] = ((fTemp36 <= 0.0) ? fSlow75 : (fRec42[1] + ((fSlow75 - fRec42[1]) / fTemp36)));
			double fTemp37 = (fRec40[1] + (fSlow72 / fRec42[0]));
			fRec40[0] = (fTemp37 - std::floor(fTemp37));
			double fTemp38 = (fRec40[0] - std::floor(fRec40[0]));
			fVec5[0] = fTemp38;
			int iTemp39 = ((fTemp38 > 0.001) * (fVec5[1] <= 0.001));
			fRec39[0] = ((fRec39[1] * double((1 - iTemp39))) + (fRec42[0] * double(iTemp39)));
			double fTemp40 = (fConst3 * (fRec39[0] * fTemp38));
			int iTemp41 = int(fTemp40);
			double fTemp42 = std::floor(fTemp40);
			double fTemp43 = (0.5 * fTemp38);
			double fTemp44 = (65536.0 * (fTemp43 - std::floor(fTemp43)));
			int iTemp45 = int(fTemp44);
			double fTemp46 = ftbl0FilDeSoi1PanStereoSIG0[iTemp45];
			double fTemp47 = (fRec40[0] + (0.25 - std::floor((fRec40[0] + 0.25))));
			fVec6[0] = fTemp47;
			int iTemp48 = ((fTemp47 > 0.001) * (fVec6[1] <= 0.001));
			fRec43[0] = ((fRec43[1] * double((1 - iTemp48))) + (fRec42[0] * double(iTemp48)));
			double fTemp49 = (fConst3 * (fRec43[0] * fTemp47));
			int iTemp50 = int(fTemp49);
			double fTemp51 = std::floor(fTemp49);
			double fTemp52 = (0.5 * fTemp47);
			double fTemp53 = (65536.0 * (fTemp52 - std::floor(fTemp52)));
			int iTemp54 = int(fTemp53);
			double fTemp55 = ftbl0FilDeSoi1PanStereoSIG0[iTemp54];
			double fTemp56 = (fRec40[0] + (0.5 - std::floor((fRec40[0] + 0.5))));
			fVec7[0] = fTemp56;
			int iTemp57 = ((fTemp56 > 0.001) * (fVec7[1] <= 0.001));
			fRec44[0] = ((fRec44[1] * double((1 - iTemp57))) + (fRec42[0] * double(iTemp57)));
			double fTemp58 = (fConst3 * (fRec44[0] * fTemp56));
			int iTemp59 = int(fTemp58);
			double fTemp60 = std::floor(fTemp58);
			double fTemp61 = (0.5 * fTemp56);
			double fTemp62 = (65536.0 * (fTemp61 - std::floor(fTemp61)));
			int iTemp63 = int(fTemp62);
			double fTemp64 = ftbl0FilDeSoi1PanStereoSIG0[iTemp63];
			double fTemp65 = (fRec40[0] + (0.75 - std::floor((fRec40[0] + 0.75))));
			fVec8[0] = fTemp65;
			int iTemp66 = ((fTemp65 > 0.001) * (fVec8[1] <= 0.001));
			fRec45[0] = ((fRec45[1] * double((1 - iTemp66))) + (fRec42[0] * double(iTemp66)));
			double fTemp67 = (fConst3 * (fRec45[0] * fTemp65));
			int iTemp68 = int(fTemp67);
			double fTemp69 = std::floor(fTemp67);
			double fTemp70 = (0.5 * fTemp65);
			double fTemp71 = (65536.0 * (fTemp70 - std::floor(fTemp70)));
			int iTemp72 = int(fTemp71);
			double fTemp73 = ftbl0FilDeSoi1PanStereoSIG0[iTemp72];
			fRec1[0] = (((((((fVec3[((IOTA - (iTemp41 & 262143)) & 262143)] * (fTemp42 + (1.0 - fTemp40))) + ((fTemp40 - fTemp42) * fVec3[((IOTA - ((iTemp41 + 1) & 262143)) & 262143)])) * (fTemp46 + ((fTemp44 - std::floor(fTemp44)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp45 + 1) % 65536)] - fTemp46)))) + (((fVec3[((IOTA - (iTemp50 & 262143)) & 262143)] * (fTemp51 + (1.0 - fTemp49))) + ((fTemp49 - fTemp51) * fVec3[((IOTA - ((iTemp50 + 1) & 262143)) & 262143)])) * (fTemp55 + ((fTemp53 - std::floor(fTemp53)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp54 + 1) % 65536)] - fTemp55))))) + (((fVec3[((IOTA - (iTemp59 & 262143)) & 262143)] * (fTemp60 + (1.0 - fTemp58))) + ((fTemp58 - fTemp60) * fVec3[((IOTA - ((iTemp59 + 1) & 262143)) & 262143)])) * (fTemp64 + ((fTemp62 - std::floor(fTemp62)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp63 + 1) % 65536)] - fTemp64))))) + (((fVec3[((IOTA - (iTemp68 & 262143)) & 262143)] * (fTemp69 + (1.0 - fTemp67))) + ((fTemp67 - fTemp69) * fVec3[((IOTA - ((iTemp68 + 1) & 262143)) & 262143)])) * (fTemp73 + ((fTemp71 - std::floor(fTemp71)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp72 + 1) % 65536)] - fTemp73))))) + (fSlow76 * fTemp34));
			fRec46[0] = (fSlow93 + (fSlow0 * fRec46[1]));
			double fTemp74 = (((((((((((((((((fSlow77 * fTemp5) + (fSlow78 * fTemp6)) + (fSlow79 * fTemp7)) + (fSlow80 * fTemp8)) + (fSlow81 * fTemp9)) + (fSlow82 * fTemp10)) + (fSlow83 * fTemp11)) + (fSlow84 * fTemp12)) + (fSlow85 * fTemp13)) + (fSlow86 * fTemp14)) + (fSlow87 * fTemp15)) + (fSlow88 * fTemp16)) + (fSlow89 * fTemp17)) + (fSlow90 * fTemp18)) + (fSlow91 * fTemp19)) + (fSlow92 * fTemp20)) + (((fTemp21 * fRec46[0]) * fTemp22) * fTemp23));
			fVec9[(IOTA & 1048575)] = fTemp74;
			iRec47[0] = ((iTemp27 * iRec47[1]) + (iSlow94 * iTemp26));
			iRec48[0] = ((iTemp30 * iRec48[1]) + (iSlow94 * iTemp29));
			double fTemp75 = ((0.5 * (fTemp4 * fVec9[((IOTA - (iRec47[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec9[((IOTA - (iRec48[0] & 1048575)) & 1048575)]));
			int iTemp76 = (fTemp75 > 1.0);
			int iTemp77 = (fTemp75 < -1.0);
			double fTemp78 = (double((iTemp76 - iTemp77)) + (fTemp75 * double(((1 - iTemp77) * (1 - iTemp76)))));
			double fTemp79 = (fSlow7 * fTemp78);
			fVec10[(IOTA & 262143)] = fTemp79;
			double fTemp80 = (fRec50[1] + (fSlow95 / fRec42[0]));
			fRec50[0] = (fTemp80 - std::floor(fTemp80));
			double fTemp81 = (fRec50[0] - std::floor(fRec50[0]));
			fVec11[0] = fTemp81;
			int iTemp82 = ((fTemp81 > 0.001) * (fVec11[1] <= 0.001));
			fRec49[0] = ((fRec49[1] * double((1 - iTemp82))) + (fRec42[0] * double(iTemp82)));
			double fTemp83 = (fConst3 * (fRec49[0] * fTemp81));
			int iTemp84 = int(fTemp83);
			double fTemp85 = std::floor(fTemp83);
			double fTemp86 = (0.5 * fTemp81);
			double fTemp87 = (65536.0 * (fTemp86 - std::floor(fTemp86)));
			int iTemp88 = int(fTemp87);
			double fTemp89 = ftbl0FilDeSoi1PanStereoSIG0[iTemp88];
			double fTemp90 = (fRec50[0] + (0.25 - std::floor((fRec50[0] + 0.25))));
			fVec12[0] = fTemp90;
			int iTemp91 = ((fTemp90 > 0.001) * (fVec12[1] <= 0.001));
			fRec51[0] = ((fRec51[1] * double((1 - iTemp91))) + (fRec42[0] * double(iTemp91)));
			double fTemp92 = (fConst3 * (fRec51[0] * fTemp90));
			int iTemp93 = int(fTemp92);
			double fTemp94 = std::floor(fTemp92);
			double fTemp95 = (0.5 * fTemp90);
			double fTemp96 = (65536.0 * (fTemp95 - std::floor(fTemp95)));
			int iTemp97 = int(fTemp96);
			double fTemp98 = ftbl0FilDeSoi1PanStereoSIG0[iTemp97];
			double fTemp99 = (fRec50[0] + (0.5 - std::floor((fRec50[0] + 0.5))));
			fVec13[0] = fTemp99;
			int iTemp100 = ((fTemp99 > 0.001) * (fVec13[1] <= 0.001));
			fRec52[0] = ((fRec52[1] * double((1 - iTemp100))) + (fRec42[0] * double(iTemp100)));
			double fTemp101 = (fConst3 * (fRec52[0] * fTemp99));
			int iTemp102 = int(fTemp101);
			double fTemp103 = std::floor(fTemp101);
			double fTemp104 = (0.5 * fTemp99);
			double fTemp105 = (65536.0 * (fTemp104 - std::floor(fTemp104)));
			int iTemp106 = int(fTemp105);
			double fTemp107 = ftbl0FilDeSoi1PanStereoSIG0[iTemp106];
			double fTemp108 = (fRec50[0] + (0.75 - std::floor((fRec50[0] + 0.75))));
			fVec14[0] = fTemp108;
			int iTemp109 = ((fTemp108 > 0.001) * (fVec14[1] <= 0.001));
			fRec53[0] = ((fRec53[1] * double((1 - iTemp109))) + (fRec42[0] * double(iTemp109)));
			double fTemp110 = (fConst3 * (fRec53[0] * fTemp108));
			int iTemp111 = int(fTemp110);
			double fTemp112 = std::floor(fTemp110);
			double fTemp113 = (0.5 * fTemp108);
			double fTemp114 = (65536.0 * (fTemp113 - std::floor(fTemp113)));
			int iTemp115 = int(fTemp114);
			double fTemp116 = ftbl0FilDeSoi1PanStereoSIG0[iTemp115];
			fRec2[0] = (((((((fVec10[((IOTA - (iTemp84 & 262143)) & 262143)] * (fTemp85 + (1.0 - fTemp83))) + ((fTemp83 - fTemp85) * fVec10[((IOTA - ((iTemp84 + 1) & 262143)) & 262143)])) * (fTemp89 + ((fTemp87 - std::floor(fTemp87)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp88 + 1) % 65536)] - fTemp89)))) + (((fVec10[((IOTA - (iTemp93 & 262143)) & 262143)] * (fTemp94 + (1.0 - fTemp92))) + ((fTemp92 - fTemp94) * fVec10[((IOTA - ((iTemp93 + 1) & 262143)) & 262143)])) * (fTemp98 + ((fTemp96 - std::floor(fTemp96)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp97 + 1) % 65536)] - fTemp98))))) + (((fVec10[((IOTA - (iTemp102 & 262143)) & 262143)] * (fTemp103 + (1.0 - fTemp101))) + ((fTemp101 - fTemp103) * fVec10[((IOTA - ((iTemp102 + 1) & 262143)) & 262143)])) * (fTemp107 + ((fTemp105 - std::floor(fTemp105)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp106 + 1) % 65536)] - fTemp107))))) + (((fVec10[((IOTA - (iTemp111 & 262143)) & 262143)] * (fTemp112 + (1.0 - fTemp110))) + ((fTemp110 - fTemp112) * fVec10[((IOTA - ((iTemp111 + 1) & 262143)) & 262143)])) * (fTemp116 + ((fTemp114 - std::floor(fTemp114)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp115 + 1) % 65536)] - fTemp116))))) + (fSlow96 * fTemp78));
			fRec54[0] = (fSlow113 + (fSlow0 * fRec54[1]));
			double fTemp117 = (((((((((((((((((fSlow97 * fTemp5) + (fSlow98 * fTemp6)) + (fSlow99 * fTemp7)) + (fSlow100 * fTemp8)) + (fSlow101 * fTemp9)) + (fSlow102 * fTemp10)) + (fSlow103 * fTemp11)) + (fSlow104 * fTemp12)) + (fSlow105 * fTemp13)) + (fSlow106 * fTemp14)) + (fSlow107 * fTemp15)) + (fSlow108 * fTemp16)) + (fSlow109 * fTemp17)) + (fSlow110 * fTemp18)) + (fSlow111 * fTemp19)) + (fSlow112 * fTemp20)) + (((fTemp21 * fRec54[0]) * fTemp22) * fTemp23));
			fVec15[(IOTA & 1048575)] = fTemp117;
			iRec55[0] = ((iTemp27 * iRec55[1]) + (iSlow114 * iTemp26));
			iRec56[0] = ((iTemp30 * iRec56[1]) + (iSlow114 * iTemp29));
			double fTemp118 = ((0.5 * (fTemp4 * fVec15[((IOTA - (iRec55[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec15[((IOTA - (iRec56[0] & 1048575)) & 1048575)]));
			int iTemp119 = (fTemp118 > 1.0);
			int iTemp120 = (fTemp118 < -1.0);
			double fTemp121 = (double((iTemp119 - iTemp120)) + (fTemp118 * double(((1 - iTemp120) * (1 - iTemp119)))));
			double fTemp122 = (fSlow11 * fTemp121);
			fVec16[(IOTA & 262143)] = fTemp122;
			double fTemp123 = (fRec58[1] + (fSlow115 / fRec42[0]));
			fRec58[0] = (fTemp123 - std::floor(fTemp123));
			double fTemp124 = (fRec58[0] - std::floor(fRec58[0]));
			fVec17[0] = fTemp124;
			int iTemp125 = ((fTemp124 > 0.001) * (fVec17[1] <= 0.001));
			fRec57[0] = ((fRec57[1] * double((1 - iTemp125))) + (fRec42[0] * double(iTemp125)));
			double fTemp126 = (fConst3 * (fRec57[0] * fTemp124));
			int iTemp127 = int(fTemp126);
			double fTemp128 = std::floor(fTemp126);
			double fTemp129 = (0.5 * fTemp124);
			double fTemp130 = (65536.0 * (fTemp129 - std::floor(fTemp129)));
			int iTemp131 = int(fTemp130);
			double fTemp132 = ftbl0FilDeSoi1PanStereoSIG0[iTemp131];
			double fTemp133 = (fRec58[0] + (0.25 - std::floor((fRec58[0] + 0.25))));
			fVec18[0] = fTemp133;
			int iTemp134 = ((fTemp133 > 0.001) * (fVec18[1] <= 0.001));
			fRec59[0] = ((fRec59[1] * double((1 - iTemp134))) + (fRec42[0] * double(iTemp134)));
			double fTemp135 = (fConst3 * (fRec59[0] * fTemp133));
			int iTemp136 = int(fTemp135);
			double fTemp137 = std::floor(fTemp135);
			double fTemp138 = (0.5 * fTemp133);
			double fTemp139 = (65536.0 * (fTemp138 - std::floor(fTemp138)));
			int iTemp140 = int(fTemp139);
			double fTemp141 = ftbl0FilDeSoi1PanStereoSIG0[iTemp140];
			double fTemp142 = (fRec58[0] + (0.5 - std::floor((fRec58[0] + 0.5))));
			fVec19[0] = fTemp142;
			int iTemp143 = ((fTemp142 > 0.001) * (fVec19[1] <= 0.001));
			fRec60[0] = ((fRec60[1] * double((1 - iTemp143))) + (fRec42[0] * double(iTemp143)));
			double fTemp144 = (fConst3 * (fRec60[0] * fTemp142));
			int iTemp145 = int(fTemp144);
			double fTemp146 = std::floor(fTemp144);
			double fTemp147 = (0.5 * fTemp142);
			double fTemp148 = (65536.0 * (fTemp147 - std::floor(fTemp147)));
			int iTemp149 = int(fTemp148);
			double fTemp150 = ftbl0FilDeSoi1PanStereoSIG0[iTemp149];
			double fTemp151 = (fRec58[0] + (0.75 - std::floor((fRec58[0] + 0.75))));
			fVec20[0] = fTemp151;
			int iTemp152 = ((fTemp151 > 0.001) * (fVec20[1] <= 0.001));
			fRec61[0] = ((fRec61[1] * double((1 - iTemp152))) + (fRec42[0] * double(iTemp152)));
			double fTemp153 = (fConst3 * (fRec61[0] * fTemp151));
			int iTemp154 = int(fTemp153);
			double fTemp155 = std::floor(fTemp153);
			double fTemp156 = (0.5 * fTemp151);
			double fTemp157 = (65536.0 * (fTemp156 - std::floor(fTemp156)));
			int iTemp158 = int(fTemp157);
			double fTemp159 = ftbl0FilDeSoi1PanStereoSIG0[iTemp158];
			fRec3[0] = (((((((fVec16[((IOTA - (iTemp127 & 262143)) & 262143)] * (fTemp128 + (1.0 - fTemp126))) + ((fTemp126 - fTemp128) * fVec16[((IOTA - ((iTemp127 + 1) & 262143)) & 262143)])) * (fTemp132 + ((fTemp130 - std::floor(fTemp130)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp131 + 1) % 65536)] - fTemp132)))) + (((fVec16[((IOTA - (iTemp136 & 262143)) & 262143)] * (fTemp137 + (1.0 - fTemp135))) + ((fTemp135 - fTemp137) * fVec16[((IOTA - ((iTemp136 + 1) & 262143)) & 262143)])) * (fTemp141 + ((fTemp139 - std::floor(fTemp139)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp140 + 1) % 65536)] - fTemp141))))) + (((fVec16[((IOTA - (iTemp145 & 262143)) & 262143)] * (fTemp146 + (1.0 - fTemp144))) + ((fTemp144 - fTemp146) * fVec16[((IOTA - ((iTemp145 + 1) & 262143)) & 262143)])) * (fTemp150 + ((fTemp148 - std::floor(fTemp148)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp149 + 1) % 65536)] - fTemp150))))) + (((fVec16[((IOTA - (iTemp154 & 262143)) & 262143)] * (fTemp155 + (1.0 - fTemp153))) + ((fTemp153 - fTemp155) * fVec16[((IOTA - ((iTemp154 + 1) & 262143)) & 262143)])) * (fTemp159 + ((fTemp157 - std::floor(fTemp157)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp158 + 1) % 65536)] - fTemp159))))) + (fSlow116 * fTemp121));
			fRec62[0] = (fSlow133 + (fSlow0 * fRec62[1]));
			double fTemp160 = (((((((((((((((((fSlow117 * fTemp5) + (fSlow118 * fTemp6)) + (fSlow119 * fTemp7)) + (fSlow120 * fTemp8)) + (fSlow121 * fTemp9)) + (fSlow122 * fTemp10)) + (fSlow123 * fTemp11)) + (fSlow124 * fTemp12)) + (fSlow125 * fTemp13)) + (fSlow126 * fTemp14)) + (fSlow127 * fTemp15)) + (fSlow128 * fTemp16)) + (fSlow129 * fTemp17)) + (fSlow130 * fTemp18)) + (fSlow131 * fTemp19)) + (fSlow132 * fTemp20)) + (((fTemp21 * fRec62[0]) * fTemp22) * fTemp23));
			fVec21[(IOTA & 1048575)] = fTemp160;
			iRec63[0] = ((iTemp27 * iRec63[1]) + (iSlow134 * iTemp26));
			iRec64[0] = ((iTemp30 * iRec64[1]) + (iSlow134 * iTemp29));
			double fTemp161 = ((0.5 * (fTemp4 * fVec21[((IOTA - (iRec63[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec21[((IOTA - (iRec64[0] & 1048575)) & 1048575)]));
			int iTemp162 = (fTemp161 > 1.0);
			int iTemp163 = (fTemp161 < -1.0);
			double fTemp164 = (double((iTemp162 - iTemp163)) + (fTemp161 * double(((1 - iTemp163) * (1 - iTemp162)))));
			double fTemp165 = (fSlow15 * fTemp164);
			fVec22[(IOTA & 262143)] = fTemp165;
			double fTemp166 = (fRec66[1] + (fSlow135 / fRec42[0]));
			fRec66[0] = (fTemp166 - std::floor(fTemp166));
			double fTemp167 = (fRec66[0] - std::floor(fRec66[0]));
			fVec23[0] = fTemp167;
			int iTemp168 = ((fTemp167 > 0.001) * (fVec23[1] <= 0.001));
			fRec65[0] = ((fRec65[1] * double((1 - iTemp168))) + (fRec42[0] * double(iTemp168)));
			double fTemp169 = (fConst3 * (fRec65[0] * fTemp167));
			int iTemp170 = int(fTemp169);
			double fTemp171 = std::floor(fTemp169);
			double fTemp172 = (0.5 * fTemp167);
			double fTemp173 = (65536.0 * (fTemp172 - std::floor(fTemp172)));
			int iTemp174 = int(fTemp173);
			double fTemp175 = ftbl0FilDeSoi1PanStereoSIG0[iTemp174];
			double fTemp176 = (fRec66[0] + (0.25 - std::floor((fRec66[0] + 0.25))));
			fVec24[0] = fTemp176;
			int iTemp177 = ((fTemp176 > 0.001) * (fVec24[1] <= 0.001));
			fRec67[0] = ((fRec67[1] * double((1 - iTemp177))) + (fRec42[0] * double(iTemp177)));
			double fTemp178 = (fConst3 * (fRec67[0] * fTemp176));
			int iTemp179 = int(fTemp178);
			double fTemp180 = std::floor(fTemp178);
			double fTemp181 = (0.5 * fTemp176);
			double fTemp182 = (65536.0 * (fTemp181 - std::floor(fTemp181)));
			int iTemp183 = int(fTemp182);
			double fTemp184 = ftbl0FilDeSoi1PanStereoSIG0[iTemp183];
			double fTemp185 = (fRec66[0] + (0.5 - std::floor((fRec66[0] + 0.5))));
			fVec25[0] = fTemp185;
			int iTemp186 = ((fTemp185 > 0.001) * (fVec25[1] <= 0.001));
			fRec68[0] = ((fRec68[1] * double((1 - iTemp186))) + (fRec42[0] * double(iTemp186)));
			double fTemp187 = (fConst3 * (fRec68[0] * fTemp185));
			int iTemp188 = int(fTemp187);
			double fTemp189 = std::floor(fTemp187);
			double fTemp190 = (0.5 * fTemp185);
			double fTemp191 = (65536.0 * (fTemp190 - std::floor(fTemp190)));
			int iTemp192 = int(fTemp191);
			double fTemp193 = ftbl0FilDeSoi1PanStereoSIG0[iTemp192];
			double fTemp194 = (fRec66[0] + (0.75 - std::floor((fRec66[0] + 0.75))));
			fVec26[0] = fTemp194;
			int iTemp195 = ((fTemp194 > 0.001) * (fVec26[1] <= 0.001));
			fRec69[0] = ((fRec69[1] * double((1 - iTemp195))) + (fRec42[0] * double(iTemp195)));
			double fTemp196 = (fConst3 * (fRec69[0] * fTemp194));
			int iTemp197 = int(fTemp196);
			double fTemp198 = std::floor(fTemp196);
			double fTemp199 = (0.5 * fTemp194);
			double fTemp200 = (65536.0 * (fTemp199 - std::floor(fTemp199)));
			int iTemp201 = int(fTemp200);
			double fTemp202 = ftbl0FilDeSoi1PanStereoSIG0[iTemp201];
			fRec4[0] = (((((((fVec22[((IOTA - (iTemp170 & 262143)) & 262143)] * (fTemp171 + (1.0 - fTemp169))) + ((fTemp169 - fTemp171) * fVec22[((IOTA - ((iTemp170 + 1) & 262143)) & 262143)])) * (fTemp175 + ((fTemp173 - std::floor(fTemp173)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp174 + 1) % 65536)] - fTemp175)))) + (((fVec22[((IOTA - (iTemp179 & 262143)) & 262143)] * (fTemp180 + (1.0 - fTemp178))) + ((fTemp178 - fTemp180) * fVec22[((IOTA - ((iTemp179 + 1) & 262143)) & 262143)])) * (fTemp184 + ((fTemp182 - std::floor(fTemp182)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp183 + 1) % 65536)] - fTemp184))))) + (((fVec22[((IOTA - (iTemp188 & 262143)) & 262143)] * (fTemp189 + (1.0 - fTemp187))) + ((fTemp187 - fTemp189) * fVec22[((IOTA - ((iTemp188 + 1) & 262143)) & 262143)])) * (fTemp193 + ((fTemp191 - std::floor(fTemp191)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp192 + 1) % 65536)] - fTemp193))))) + (((fVec22[((IOTA - (iTemp197 & 262143)) & 262143)] * (fTemp198 + (1.0 - fTemp196))) + ((fTemp196 - fTemp198) * fVec22[((IOTA - ((iTemp197 + 1) & 262143)) & 262143)])) * (fTemp202 + ((fTemp200 - std::floor(fTemp200)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp201 + 1) % 65536)] - fTemp202))))) + (fSlow136 * fTemp164));
			fRec70[0] = (fSlow153 + (fSlow0 * fRec70[1]));
			double fTemp203 = (((((((((((((((((fSlow137 * fTemp5) + (fSlow138 * fTemp6)) + (fSlow139 * fTemp7)) + (fSlow140 * fTemp8)) + (fSlow141 * fTemp9)) + (fSlow142 * fTemp10)) + (fSlow143 * fTemp11)) + (fSlow144 * fTemp12)) + (fSlow145 * fTemp13)) + (fSlow146 * fTemp14)) + (fSlow147 * fTemp15)) + (fSlow148 * fTemp16)) + (fSlow149 * fTemp17)) + (fSlow150 * fTemp18)) + (fSlow151 * fTemp19)) + (fSlow152 * fTemp20)) + (((fTemp21 * fRec70[0]) * fTemp22) * fTemp23));
			fVec27[(IOTA & 1048575)] = fTemp203;
			iRec71[0] = ((iTemp27 * iRec71[1]) + (iSlow154 * iTemp26));
			iRec72[0] = ((iTemp30 * iRec72[1]) + (iSlow154 * iTemp29));
			double fTemp204 = ((0.5 * (fTemp4 * fVec27[((IOTA - (iRec71[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec27[((IOTA - (iRec72[0] & 1048575)) & 1048575)]));
			int iTemp205 = (fTemp204 > 1.0);
			int iTemp206 = (fTemp204 < -1.0);
			double fTemp207 = (double((iTemp205 - iTemp206)) + (fTemp204 * double(((1 - iTemp206) * (1 - iTemp205)))));
			double fTemp208 = (fSlow19 * fTemp207);
			fVec28[(IOTA & 262143)] = fTemp208;
			double fTemp209 = (fRec74[1] + (fSlow155 / fRec42[0]));
			fRec74[0] = (fTemp209 - std::floor(fTemp209));
			double fTemp210 = (fRec74[0] - std::floor(fRec74[0]));
			fVec29[0] = fTemp210;
			int iTemp211 = ((fTemp210 > 0.001) * (fVec29[1] <= 0.001));
			fRec73[0] = ((fRec73[1] * double((1 - iTemp211))) + (fRec42[0] * double(iTemp211)));
			double fTemp212 = (fConst3 * (fRec73[0] * fTemp210));
			int iTemp213 = int(fTemp212);
			double fTemp214 = std::floor(fTemp212);
			double fTemp215 = (0.5 * fTemp210);
			double fTemp216 = (65536.0 * (fTemp215 - std::floor(fTemp215)));
			int iTemp217 = int(fTemp216);
			double fTemp218 = ftbl0FilDeSoi1PanStereoSIG0[iTemp217];
			double fTemp219 = (fRec74[0] + (0.25 - std::floor((fRec74[0] + 0.25))));
			fVec30[0] = fTemp219;
			int iTemp220 = ((fTemp219 > 0.001) * (fVec30[1] <= 0.001));
			fRec75[0] = ((fRec75[1] * double((1 - iTemp220))) + (fRec42[0] * double(iTemp220)));
			double fTemp221 = (fConst3 * (fRec75[0] * fTemp219));
			int iTemp222 = int(fTemp221);
			double fTemp223 = std::floor(fTemp221);
			double fTemp224 = (0.5 * fTemp219);
			double fTemp225 = (65536.0 * (fTemp224 - std::floor(fTemp224)));
			int iTemp226 = int(fTemp225);
			double fTemp227 = ftbl0FilDeSoi1PanStereoSIG0[iTemp226];
			double fTemp228 = (fRec74[0] + (0.5 - std::floor((fRec74[0] + 0.5))));
			fVec31[0] = fTemp228;
			int iTemp229 = ((fTemp228 > 0.001) * (fVec31[1] <= 0.001));
			fRec76[0] = ((fRec76[1] * double((1 - iTemp229))) + (fRec42[0] * double(iTemp229)));
			double fTemp230 = (fConst3 * (fRec76[0] * fTemp228));
			int iTemp231 = int(fTemp230);
			double fTemp232 = std::floor(fTemp230);
			double fTemp233 = (0.5 * fTemp228);
			double fTemp234 = (65536.0 * (fTemp233 - std::floor(fTemp233)));
			int iTemp235 = int(fTemp234);
			double fTemp236 = ftbl0FilDeSoi1PanStereoSIG0[iTemp235];
			double fTemp237 = (fRec74[0] + (0.75 - std::floor((fRec74[0] + 0.75))));
			fVec32[0] = fTemp237;
			int iTemp238 = ((fTemp237 > 0.001) * (fVec32[1] <= 0.001));
			fRec77[0] = ((fRec77[1] * double((1 - iTemp238))) + (fRec42[0] * double(iTemp238)));
			double fTemp239 = (fConst3 * (fRec77[0] * fTemp237));
			int iTemp240 = int(fTemp239);
			double fTemp241 = std::floor(fTemp239);
			double fTemp242 = (0.5 * fTemp237);
			double fTemp243 = (65536.0 * (fTemp242 - std::floor(fTemp242)));
			int iTemp244 = int(fTemp243);
			double fTemp245 = ftbl0FilDeSoi1PanStereoSIG0[iTemp244];
			fRec5[0] = (((((((fVec28[((IOTA - (iTemp213 & 262143)) & 262143)] * (fTemp214 + (1.0 - fTemp212))) + ((fTemp212 - fTemp214) * fVec28[((IOTA - ((iTemp213 + 1) & 262143)) & 262143)])) * (fTemp218 + ((fTemp216 - std::floor(fTemp216)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp217 + 1) % 65536)] - fTemp218)))) + (((fVec28[((IOTA - (iTemp222 & 262143)) & 262143)] * (fTemp223 + (1.0 - fTemp221))) + ((fTemp221 - fTemp223) * fVec28[((IOTA - ((iTemp222 + 1) & 262143)) & 262143)])) * (fTemp227 + ((fTemp225 - std::floor(fTemp225)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp226 + 1) % 65536)] - fTemp227))))) + (((fVec28[((IOTA - (iTemp231 & 262143)) & 262143)] * (fTemp232 + (1.0 - fTemp230))) + ((fTemp230 - fTemp232) * fVec28[((IOTA - ((iTemp231 + 1) & 262143)) & 262143)])) * (fTemp236 + ((fTemp234 - std::floor(fTemp234)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp235 + 1) % 65536)] - fTemp236))))) + (((fVec28[((IOTA - (iTemp240 & 262143)) & 262143)] * (fTemp241 + (1.0 - fTemp239))) + ((fTemp239 - fTemp241) * fVec28[((IOTA - ((iTemp240 + 1) & 262143)) & 262143)])) * (fTemp245 + ((fTemp243 - std::floor(fTemp243)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp244 + 1) % 65536)] - fTemp245))))) + (fSlow156 * fTemp207));
			fRec78[0] = (fSlow173 + (fSlow0 * fRec78[1]));
			double fTemp246 = (((((((((((((((((fSlow157 * fTemp5) + (fSlow158 * fTemp6)) + (fSlow159 * fTemp7)) + (fSlow160 * fTemp8)) + (fSlow161 * fTemp9)) + (fSlow162 * fTemp10)) + (fSlow163 * fTemp11)) + (fSlow164 * fTemp12)) + (fSlow165 * fTemp13)) + (fSlow166 * fTemp14)) + (fSlow167 * fTemp15)) + (fSlow168 * fTemp16)) + (fSlow169 * fTemp17)) + (fSlow170 * fTemp18)) + (fSlow171 * fTemp19)) + (fSlow172 * fTemp20)) + (((fTemp21 * fRec78[0]) * fTemp22) * fTemp23));
			fVec33[(IOTA & 1048575)] = fTemp246;
			iRec79[0] = ((iTemp27 * iRec79[1]) + (iSlow174 * iTemp26));
			iRec80[0] = ((iTemp30 * iRec80[1]) + (iSlow174 * iTemp29));
			double fTemp247 = ((0.5 * (fTemp4 * fVec33[((IOTA - (iRec79[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec33[((IOTA - (iRec80[0] & 1048575)) & 1048575)]));
			int iTemp248 = (fTemp247 > 1.0);
			int iTemp249 = (fTemp247 < -1.0);
			double fTemp250 = (double((iTemp248 - iTemp249)) + (fTemp247 * double(((1 - iTemp249) * (1 - iTemp248)))));
			double fTemp251 = (fSlow23 * fTemp250);
			fVec34[(IOTA & 262143)] = fTemp251;
			double fTemp252 = (fRec82[1] + (fSlow175 / fRec42[0]));
			fRec82[0] = (fTemp252 - std::floor(fTemp252));
			double fTemp253 = (fRec82[0] - std::floor(fRec82[0]));
			fVec35[0] = fTemp253;
			int iTemp254 = ((fTemp253 > 0.001) * (fVec35[1] <= 0.001));
			fRec81[0] = ((fRec81[1] * double((1 - iTemp254))) + (fRec42[0] * double(iTemp254)));
			double fTemp255 = (fConst3 * (fRec81[0] * fTemp253));
			int iTemp256 = int(fTemp255);
			double fTemp257 = std::floor(fTemp255);
			double fTemp258 = (0.5 * fTemp253);
			double fTemp259 = (65536.0 * (fTemp258 - std::floor(fTemp258)));
			int iTemp260 = int(fTemp259);
			double fTemp261 = ftbl0FilDeSoi1PanStereoSIG0[iTemp260];
			double fTemp262 = (fRec82[0] + (0.25 - std::floor((fRec82[0] + 0.25))));
			fVec36[0] = fTemp262;
			int iTemp263 = ((fTemp262 > 0.001) * (fVec36[1] <= 0.001));
			fRec83[0] = ((fRec83[1] * double((1 - iTemp263))) + (fRec42[0] * double(iTemp263)));
			double fTemp264 = (fConst3 * (fRec83[0] * fTemp262));
			int iTemp265 = int(fTemp264);
			double fTemp266 = std::floor(fTemp264);
			double fTemp267 = (0.5 * fTemp262);
			double fTemp268 = (65536.0 * (fTemp267 - std::floor(fTemp267)));
			int iTemp269 = int(fTemp268);
			double fTemp270 = ftbl0FilDeSoi1PanStereoSIG0[iTemp269];
			double fTemp271 = (fRec82[0] + (0.5 - std::floor((fRec82[0] + 0.5))));
			fVec37[0] = fTemp271;
			int iTemp272 = ((fTemp271 > 0.001) * (fVec37[1] <= 0.001));
			fRec84[0] = ((fRec84[1] * double((1 - iTemp272))) + (fRec42[0] * double(iTemp272)));
			double fTemp273 = (fConst3 * (fRec84[0] * fTemp271));
			int iTemp274 = int(fTemp273);
			double fTemp275 = std::floor(fTemp273);
			double fTemp276 = (0.5 * fTemp271);
			double fTemp277 = (65536.0 * (fTemp276 - std::floor(fTemp276)));
			int iTemp278 = int(fTemp277);
			double fTemp279 = ftbl0FilDeSoi1PanStereoSIG0[iTemp278];
			double fTemp280 = (fRec82[0] + (0.75 - std::floor((fRec82[0] + 0.75))));
			fVec38[0] = fTemp280;
			int iTemp281 = ((fTemp280 > 0.001) * (fVec38[1] <= 0.001));
			fRec85[0] = ((fRec85[1] * double((1 - iTemp281))) + (fRec42[0] * double(iTemp281)));
			double fTemp282 = (fConst3 * (fRec85[0] * fTemp280));
			int iTemp283 = int(fTemp282);
			double fTemp284 = std::floor(fTemp282);
			double fTemp285 = (0.5 * fTemp280);
			double fTemp286 = (65536.0 * (fTemp285 - std::floor(fTemp285)));
			int iTemp287 = int(fTemp286);
			double fTemp288 = ftbl0FilDeSoi1PanStereoSIG0[iTemp287];
			fRec6[0] = (((((((fVec34[((IOTA - (iTemp256 & 262143)) & 262143)] * (fTemp257 + (1.0 - fTemp255))) + ((fTemp255 - fTemp257) * fVec34[((IOTA - ((iTemp256 + 1) & 262143)) & 262143)])) * (fTemp261 + ((fTemp259 - std::floor(fTemp259)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp260 + 1) % 65536)] - fTemp261)))) + (((fVec34[((IOTA - (iTemp265 & 262143)) & 262143)] * (fTemp266 + (1.0 - fTemp264))) + ((fTemp264 - fTemp266) * fVec34[((IOTA - ((iTemp265 + 1) & 262143)) & 262143)])) * (fTemp270 + ((fTemp268 - std::floor(fTemp268)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp269 + 1) % 65536)] - fTemp270))))) + (((fVec34[((IOTA - (iTemp274 & 262143)) & 262143)] * (fTemp275 + (1.0 - fTemp273))) + ((fTemp273 - fTemp275) * fVec34[((IOTA - ((iTemp274 + 1) & 262143)) & 262143)])) * (fTemp279 + ((fTemp277 - std::floor(fTemp277)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp278 + 1) % 65536)] - fTemp279))))) + (((fVec34[((IOTA - (iTemp283 & 262143)) & 262143)] * (fTemp284 + (1.0 - fTemp282))) + ((fTemp282 - fTemp284) * fVec34[((IOTA - ((iTemp283 + 1) & 262143)) & 262143)])) * (fTemp288 + ((fTemp286 - std::floor(fTemp286)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp287 + 1) % 65536)] - fTemp288))))) + (fSlow176 * fTemp250));
			fRec86[0] = (fSlow193 + (fSlow0 * fRec86[1]));
			double fTemp289 = (((((((((((((((((fSlow177 * fTemp5) + (fSlow178 * fTemp6)) + (fSlow179 * fTemp7)) + (fSlow180 * fTemp8)) + (fSlow181 * fTemp9)) + (fSlow182 * fTemp10)) + (fSlow183 * fTemp11)) + (fSlow184 * fTemp12)) + (fSlow185 * fTemp13)) + (fSlow186 * fTemp14)) + (fSlow187 * fTemp15)) + (fSlow188 * fTemp16)) + (fSlow189 * fTemp17)) + (fSlow190 * fTemp18)) + (fSlow191 * fTemp19)) + (fSlow192 * fTemp20)) + (((fTemp21 * fRec86[0]) * fTemp22) * fTemp23));
			fVec39[(IOTA & 1048575)] = fTemp289;
			iRec87[0] = ((iTemp27 * iRec87[1]) + (iSlow194 * iTemp26));
			iRec88[0] = ((iTemp30 * iRec88[1]) + (iSlow194 * iTemp29));
			double fTemp290 = ((0.5 * (fTemp4 * fVec39[((IOTA - (iRec87[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec39[((IOTA - (iRec88[0] & 1048575)) & 1048575)]));
			int iTemp291 = (fTemp290 > 1.0);
			int iTemp292 = (fTemp290 < -1.0);
			double fTemp293 = (double((iTemp291 - iTemp292)) + (fTemp290 * double(((1 - iTemp292) * (1 - iTemp291)))));
			double fTemp294 = (fSlow27 * fTemp293);
			fVec40[(IOTA & 262143)] = fTemp294;
			double fTemp295 = (fRec90[1] + (fSlow195 / fRec42[0]));
			fRec90[0] = (fTemp295 - std::floor(fTemp295));
			double fTemp296 = (fRec90[0] - std::floor(fRec90[0]));
			fVec41[0] = fTemp296;
			int iTemp297 = ((fTemp296 > 0.001) * (fVec41[1] <= 0.001));
			fRec89[0] = ((fRec89[1] * double((1 - iTemp297))) + (fRec42[0] * double(iTemp297)));
			double fTemp298 = (fConst3 * (fRec89[0] * fTemp296));
			int iTemp299 = int(fTemp298);
			double fTemp300 = std::floor(fTemp298);
			double fTemp301 = (0.5 * fTemp296);
			double fTemp302 = (65536.0 * (fTemp301 - std::floor(fTemp301)));
			int iTemp303 = int(fTemp302);
			double fTemp304 = ftbl0FilDeSoi1PanStereoSIG0[iTemp303];
			double fTemp305 = (fRec90[0] + (0.25 - std::floor((fRec90[0] + 0.25))));
			fVec42[0] = fTemp305;
			int iTemp306 = ((fTemp305 > 0.001) * (fVec42[1] <= 0.001));
			fRec91[0] = ((fRec91[1] * double((1 - iTemp306))) + (fRec42[0] * double(iTemp306)));
			double fTemp307 = (fConst3 * (fRec91[0] * fTemp305));
			int iTemp308 = int(fTemp307);
			double fTemp309 = std::floor(fTemp307);
			double fTemp310 = (0.5 * fTemp305);
			double fTemp311 = (65536.0 * (fTemp310 - std::floor(fTemp310)));
			int iTemp312 = int(fTemp311);
			double fTemp313 = ftbl0FilDeSoi1PanStereoSIG0[iTemp312];
			double fTemp314 = (fRec90[0] + (0.5 - std::floor((fRec90[0] + 0.5))));
			fVec43[0] = fTemp314;
			int iTemp315 = ((fTemp314 > 0.001) * (fVec43[1] <= 0.001));
			fRec92[0] = ((fRec92[1] * double((1 - iTemp315))) + (fRec42[0] * double(iTemp315)));
			double fTemp316 = (fConst3 * (fRec92[0] * fTemp314));
			int iTemp317 = int(fTemp316);
			double fTemp318 = std::floor(fTemp316);
			double fTemp319 = (0.5 * fTemp314);
			double fTemp320 = (65536.0 * (fTemp319 - std::floor(fTemp319)));
			int iTemp321 = int(fTemp320);
			double fTemp322 = ftbl0FilDeSoi1PanStereoSIG0[iTemp321];
			double fTemp323 = (fRec90[0] + (0.75 - std::floor((fRec90[0] + 0.75))));
			fVec44[0] = fTemp323;
			int iTemp324 = ((fTemp323 > 0.001) * (fVec44[1] <= 0.001));
			fRec93[0] = ((fRec93[1] * double((1 - iTemp324))) + (fRec42[0] * double(iTemp324)));
			double fTemp325 = (fConst3 * (fRec93[0] * fTemp323));
			int iTemp326 = int(fTemp325);
			double fTemp327 = std::floor(fTemp325);
			double fTemp328 = (0.5 * fTemp323);
			double fTemp329 = (65536.0 * (fTemp328 - std::floor(fTemp328)));
			int iTemp330 = int(fTemp329);
			double fTemp331 = ftbl0FilDeSoi1PanStereoSIG0[iTemp330];
			fRec7[0] = (((((((fVec40[((IOTA - (iTemp299 & 262143)) & 262143)] * (fTemp300 + (1.0 - fTemp298))) + ((fTemp298 - fTemp300) * fVec40[((IOTA - ((iTemp299 + 1) & 262143)) & 262143)])) * (fTemp304 + ((fTemp302 - std::floor(fTemp302)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp303 + 1) % 65536)] - fTemp304)))) + (((fVec40[((IOTA - (iTemp308 & 262143)) & 262143)] * (fTemp309 + (1.0 - fTemp307))) + ((fTemp307 - fTemp309) * fVec40[((IOTA - ((iTemp308 + 1) & 262143)) & 262143)])) * (fTemp313 + ((fTemp311 - std::floor(fTemp311)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp312 + 1) % 65536)] - fTemp313))))) + (((fVec40[((IOTA - (iTemp317 & 262143)) & 262143)] * (fTemp318 + (1.0 - fTemp316))) + ((fTemp316 - fTemp318) * fVec40[((IOTA - ((iTemp317 + 1) & 262143)) & 262143)])) * (fTemp322 + ((fTemp320 - std::floor(fTemp320)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp321 + 1) % 65536)] - fTemp322))))) + (((fVec40[((IOTA - (iTemp326 & 262143)) & 262143)] * (fTemp327 + (1.0 - fTemp325))) + ((fTemp325 - fTemp327) * fVec40[((IOTA - ((iTemp326 + 1) & 262143)) & 262143)])) * (fTemp331 + ((fTemp329 - std::floor(fTemp329)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp330 + 1) % 65536)] - fTemp331))))) + (fSlow196 * fTemp293));
			fRec94[0] = (fSlow213 + (fSlow0 * fRec94[1]));
			double fTemp332 = (((((((((((((((((fSlow197 * fTemp5) + (fSlow198 * fTemp6)) + (fSlow199 * fTemp7)) + (fSlow200 * fTemp8)) + (fSlow201 * fTemp9)) + (fSlow202 * fTemp10)) + (fSlow203 * fTemp11)) + (fSlow204 * fTemp12)) + (fSlow205 * fTemp13)) + (fSlow206 * fTemp14)) + (fSlow207 * fTemp15)) + (fSlow208 * fTemp16)) + (fSlow209 * fTemp17)) + (fSlow210 * fTemp18)) + (fSlow211 * fTemp19)) + (fSlow212 * fTemp20)) + (((fTemp21 * fRec94[0]) * fTemp22) * fTemp23));
			fVec45[(IOTA & 1048575)] = fTemp332;
			iRec95[0] = ((iTemp27 * iRec95[1]) + (iSlow214 * iTemp26));
			iRec96[0] = ((iTemp30 * iRec96[1]) + (iSlow214 * iTemp29));
			double fTemp333 = ((0.5 * (fTemp4 * fVec45[((IOTA - (iRec95[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec45[((IOTA - (iRec96[0] & 1048575)) & 1048575)]));
			int iTemp334 = (fTemp333 > 1.0);
			int iTemp335 = (fTemp333 < -1.0);
			double fTemp336 = (double((iTemp334 - iTemp335)) + (fTemp333 * double(((1 - iTemp335) * (1 - iTemp334)))));
			double fTemp337 = (fSlow31 * fTemp336);
			fVec46[(IOTA & 262143)] = fTemp337;
			double fTemp338 = (fRec98[1] + (fSlow215 / fRec42[0]));
			fRec98[0] = (fTemp338 - std::floor(fTemp338));
			double fTemp339 = (fRec98[0] - std::floor(fRec98[0]));
			fVec47[0] = fTemp339;
			int iTemp340 = ((fTemp339 > 0.001) * (fVec47[1] <= 0.001));
			fRec97[0] = ((fRec97[1] * double((1 - iTemp340))) + (fRec42[0] * double(iTemp340)));
			double fTemp341 = (fConst3 * (fRec97[0] * fTemp339));
			int iTemp342 = int(fTemp341);
			double fTemp343 = std::floor(fTemp341);
			double fTemp344 = (0.5 * fTemp339);
			double fTemp345 = (65536.0 * (fTemp344 - std::floor(fTemp344)));
			int iTemp346 = int(fTemp345);
			double fTemp347 = ftbl0FilDeSoi1PanStereoSIG0[iTemp346];
			double fTemp348 = (fRec98[0] + (0.25 - std::floor((fRec98[0] + 0.25))));
			fVec48[0] = fTemp348;
			int iTemp349 = ((fTemp348 > 0.001) * (fVec48[1] <= 0.001));
			fRec99[0] = ((fRec99[1] * double((1 - iTemp349))) + (fRec42[0] * double(iTemp349)));
			double fTemp350 = (fConst3 * (fRec99[0] * fTemp348));
			int iTemp351 = int(fTemp350);
			double fTemp352 = std::floor(fTemp350);
			double fTemp353 = (0.5 * fTemp348);
			double fTemp354 = (65536.0 * (fTemp353 - std::floor(fTemp353)));
			int iTemp355 = int(fTemp354);
			double fTemp356 = ftbl0FilDeSoi1PanStereoSIG0[iTemp355];
			double fTemp357 = (fRec98[0] + (0.5 - std::floor((fRec98[0] + 0.5))));
			fVec49[0] = fTemp357;
			int iTemp358 = ((fTemp357 > 0.001) * (fVec49[1] <= 0.001));
			fRec100[0] = ((fRec100[1] * double((1 - iTemp358))) + (fRec42[0] * double(iTemp358)));
			double fTemp359 = (fConst3 * (fRec100[0] * fTemp357));
			int iTemp360 = int(fTemp359);
			double fTemp361 = std::floor(fTemp359);
			double fTemp362 = (0.5 * fTemp357);
			double fTemp363 = (65536.0 * (fTemp362 - std::floor(fTemp362)));
			int iTemp364 = int(fTemp363);
			double fTemp365 = ftbl0FilDeSoi1PanStereoSIG0[iTemp364];
			double fTemp366 = (fRec98[0] + (0.75 - std::floor((fRec98[0] + 0.75))));
			fVec50[0] = fTemp366;
			int iTemp367 = ((fTemp366 > 0.001) * (fVec50[1] <= 0.001));
			fRec101[0] = ((fRec101[1] * double((1 - iTemp367))) + (fRec42[0] * double(iTemp367)));
			double fTemp368 = (fConst3 * (fRec101[0] * fTemp366));
			int iTemp369 = int(fTemp368);
			double fTemp370 = std::floor(fTemp368);
			double fTemp371 = (0.5 * fTemp366);
			double fTemp372 = (65536.0 * (fTemp371 - std::floor(fTemp371)));
			int iTemp373 = int(fTemp372);
			double fTemp374 = ftbl0FilDeSoi1PanStereoSIG0[iTemp373];
			fRec8[0] = (((((((fVec46[((IOTA - (iTemp342 & 262143)) & 262143)] * (fTemp343 + (1.0 - fTemp341))) + ((fTemp341 - fTemp343) * fVec46[((IOTA - ((iTemp342 + 1) & 262143)) & 262143)])) * (fTemp347 + ((fTemp345 - std::floor(fTemp345)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp346 + 1) % 65536)] - fTemp347)))) + (((fVec46[((IOTA - (iTemp351 & 262143)) & 262143)] * (fTemp352 + (1.0 - fTemp350))) + ((fTemp350 - fTemp352) * fVec46[((IOTA - ((iTemp351 + 1) & 262143)) & 262143)])) * (fTemp356 + ((fTemp354 - std::floor(fTemp354)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp355 + 1) % 65536)] - fTemp356))))) + (((fVec46[((IOTA - (iTemp360 & 262143)) & 262143)] * (fTemp361 + (1.0 - fTemp359))) + ((fTemp359 - fTemp361) * fVec46[((IOTA - ((iTemp360 + 1) & 262143)) & 262143)])) * (fTemp365 + ((fTemp363 - std::floor(fTemp363)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp364 + 1) % 65536)] - fTemp365))))) + (((fVec46[((IOTA - (iTemp369 & 262143)) & 262143)] * (fTemp370 + (1.0 - fTemp368))) + ((fTemp368 - fTemp370) * fVec46[((IOTA - ((iTemp369 + 1) & 262143)) & 262143)])) * (fTemp374 + ((fTemp372 - std::floor(fTemp372)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp373 + 1) % 65536)] - fTemp374))))) + (fSlow216 * fTemp336));
			fRec102[0] = (fSlow233 + (fSlow0 * fRec102[1]));
			double fTemp375 = (((((((((((((((((fSlow217 * fTemp5) + (fSlow218 * fTemp6)) + (fSlow219 * fTemp7)) + (fSlow220 * fTemp8)) + (fSlow221 * fTemp9)) + (fSlow222 * fTemp10)) + (fSlow223 * fTemp11)) + (fSlow224 * fTemp12)) + (fSlow225 * fTemp13)) + (fSlow226 * fTemp14)) + (fSlow227 * fTemp15)) + (fSlow228 * fTemp16)) + (fSlow229 * fTemp17)) + (fSlow230 * fTemp18)) + (fSlow231 * fTemp19)) + (fSlow232 * fTemp20)) + (((fTemp21 * fRec102[0]) * fTemp22) * fTemp23));
			fVec51[(IOTA & 1048575)] = fTemp375;
			iRec103[0] = ((iTemp27 * iRec103[1]) + (iSlow234 * iTemp26));
			iRec104[0] = ((iTemp30 * iRec104[1]) + (iSlow234 * iTemp29));
			double fTemp376 = ((0.5 * (fTemp4 * fVec51[((IOTA - (iRec103[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec51[((IOTA - (iRec104[0] & 1048575)) & 1048575)]));
			int iTemp377 = (fTemp376 > 1.0);
			int iTemp378 = (fTemp376 < -1.0);
			double fTemp379 = (double((iTemp377 - iTemp378)) + (fTemp376 * double(((1 - iTemp378) * (1 - iTemp377)))));
			double fTemp380 = (fSlow35 * fTemp379);
			fVec52[(IOTA & 262143)] = fTemp380;
			double fTemp381 = (fRec106[1] + (fSlow235 / fRec42[0]));
			fRec106[0] = (fTemp381 - std::floor(fTemp381));
			double fTemp382 = (fRec106[0] - std::floor(fRec106[0]));
			fVec53[0] = fTemp382;
			int iTemp383 = ((fTemp382 > 0.001) * (fVec53[1] <= 0.001));
			fRec105[0] = ((fRec105[1] * double((1 - iTemp383))) + (fRec42[0] * double(iTemp383)));
			double fTemp384 = (fConst3 * (fRec105[0] * fTemp382));
			int iTemp385 = int(fTemp384);
			double fTemp386 = std::floor(fTemp384);
			double fTemp387 = (0.5 * fTemp382);
			double fTemp388 = (65536.0 * (fTemp387 - std::floor(fTemp387)));
			int iTemp389 = int(fTemp388);
			double fTemp390 = ftbl0FilDeSoi1PanStereoSIG0[iTemp389];
			double fTemp391 = (fRec106[0] + (0.25 - std::floor((fRec106[0] + 0.25))));
			fVec54[0] = fTemp391;
			int iTemp392 = ((fTemp391 > 0.001) * (fVec54[1] <= 0.001));
			fRec107[0] = ((fRec107[1] * double((1 - iTemp392))) + (fRec42[0] * double(iTemp392)));
			double fTemp393 = (fConst3 * (fRec107[0] * fTemp391));
			int iTemp394 = int(fTemp393);
			double fTemp395 = std::floor(fTemp393);
			double fTemp396 = (0.5 * fTemp391);
			double fTemp397 = (65536.0 * (fTemp396 - std::floor(fTemp396)));
			int iTemp398 = int(fTemp397);
			double fTemp399 = ftbl0FilDeSoi1PanStereoSIG0[iTemp398];
			double fTemp400 = (fRec106[0] + (0.5 - std::floor((fRec106[0] + 0.5))));
			fVec55[0] = fTemp400;
			int iTemp401 = ((fTemp400 > 0.001) * (fVec55[1] <= 0.001));
			fRec108[0] = ((fRec108[1] * double((1 - iTemp401))) + (fRec42[0] * double(iTemp401)));
			double fTemp402 = (fConst3 * (fRec108[0] * fTemp400));
			int iTemp403 = int(fTemp402);
			double fTemp404 = std::floor(fTemp402);
			double fTemp405 = (0.5 * fTemp400);
			double fTemp406 = (65536.0 * (fTemp405 - std::floor(fTemp405)));
			int iTemp407 = int(fTemp406);
			double fTemp408 = ftbl0FilDeSoi1PanStereoSIG0[iTemp407];
			double fTemp409 = (fRec106[0] + (0.75 - std::floor((fRec106[0] + 0.75))));
			fVec56[0] = fTemp409;
			int iTemp410 = ((fTemp409 > 0.001) * (fVec56[1] <= 0.001));
			fRec109[0] = ((fRec109[1] * double((1 - iTemp410))) + (fRec42[0] * double(iTemp410)));
			double fTemp411 = (fConst3 * (fRec109[0] * fTemp409));
			int iTemp412 = int(fTemp411);
			double fTemp413 = std::floor(fTemp411);
			double fTemp414 = (0.5 * fTemp409);
			double fTemp415 = (65536.0 * (fTemp414 - std::floor(fTemp414)));
			int iTemp416 = int(fTemp415);
			double fTemp417 = ftbl0FilDeSoi1PanStereoSIG0[iTemp416];
			fRec9[0] = (((((((fVec52[((IOTA - (iTemp385 & 262143)) & 262143)] * (fTemp386 + (1.0 - fTemp384))) + ((fTemp384 - fTemp386) * fVec52[((IOTA - ((iTemp385 + 1) & 262143)) & 262143)])) * (fTemp390 + ((fTemp388 - std::floor(fTemp388)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp389 + 1) % 65536)] - fTemp390)))) + (((fVec52[((IOTA - (iTemp394 & 262143)) & 262143)] * (fTemp395 + (1.0 - fTemp393))) + ((fTemp393 - fTemp395) * fVec52[((IOTA - ((iTemp394 + 1) & 262143)) & 262143)])) * (fTemp399 + ((fTemp397 - std::floor(fTemp397)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp398 + 1) % 65536)] - fTemp399))))) + (((fVec52[((IOTA - (iTemp403 & 262143)) & 262143)] * (fTemp404 + (1.0 - fTemp402))) + ((fTemp402 - fTemp404) * fVec52[((IOTA - ((iTemp403 + 1) & 262143)) & 262143)])) * (fTemp408 + ((fTemp406 - std::floor(fTemp406)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp407 + 1) % 65536)] - fTemp408))))) + (((fVec52[((IOTA - (iTemp412 & 262143)) & 262143)] * (fTemp413 + (1.0 - fTemp411))) + ((fTemp411 - fTemp413) * fVec52[((IOTA - ((iTemp412 + 1) & 262143)) & 262143)])) * (fTemp417 + ((fTemp415 - std::floor(fTemp415)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp416 + 1) % 65536)] - fTemp417))))) + (fSlow236 * fTemp379));
			fRec110[0] = (fSlow253 + (fSlow0 * fRec110[1]));
			double fTemp418 = (((((((((((((((((fSlow237 * fTemp5) + (fSlow238 * fTemp6)) + (fSlow239 * fTemp7)) + (fSlow240 * fTemp8)) + (fSlow241 * fTemp9)) + (fSlow242 * fTemp10)) + (fSlow243 * fTemp11)) + (fSlow244 * fTemp12)) + (fSlow245 * fTemp13)) + (fSlow246 * fTemp14)) + (fSlow247 * fTemp15)) + (fSlow248 * fTemp16)) + (fSlow249 * fTemp17)) + (fSlow250 * fTemp18)) + (fSlow251 * fTemp19)) + (fSlow252 * fTemp20)) + (((fTemp21 * fRec110[0]) * fTemp22) * fTemp23));
			fVec57[(IOTA & 1048575)] = fTemp418;
			iRec111[0] = ((iTemp27 * iRec111[1]) + (iSlow254 * iTemp26));
			iRec112[0] = ((iTemp30 * iRec112[1]) + (iSlow254 * iTemp29));
			double fTemp419 = ((0.5 * (fTemp4 * fVec57[((IOTA - (iRec111[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec57[((IOTA - (iRec112[0] & 1048575)) & 1048575)]));
			int iTemp420 = (fTemp419 > 1.0);
			int iTemp421 = (fTemp419 < -1.0);
			double fTemp422 = (double((iTemp420 - iTemp421)) + (fTemp419 * double(((1 - iTemp421) * (1 - iTemp420)))));
			double fTemp423 = (fSlow39 * fTemp422);
			fVec58[(IOTA & 262143)] = fTemp423;
			double fTemp424 = (fRec114[1] + (fSlow255 / fRec42[0]));
			fRec114[0] = (fTemp424 - std::floor(fTemp424));
			double fTemp425 = (fRec114[0] - std::floor(fRec114[0]));
			fVec59[0] = fTemp425;
			int iTemp426 = ((fTemp425 > 0.001) * (fVec59[1] <= 0.001));
			fRec113[0] = ((fRec113[1] * double((1 - iTemp426))) + (fRec42[0] * double(iTemp426)));
			double fTemp427 = (fConst3 * (fRec113[0] * fTemp425));
			int iTemp428 = int(fTemp427);
			double fTemp429 = std::floor(fTemp427);
			double fTemp430 = (0.5 * fTemp425);
			double fTemp431 = (65536.0 * (fTemp430 - std::floor(fTemp430)));
			int iTemp432 = int(fTemp431);
			double fTemp433 = ftbl0FilDeSoi1PanStereoSIG0[iTemp432];
			double fTemp434 = (fRec114[0] + (0.25 - std::floor((fRec114[0] + 0.25))));
			fVec60[0] = fTemp434;
			int iTemp435 = ((fTemp434 > 0.001) * (fVec60[1] <= 0.001));
			fRec115[0] = ((fRec115[1] * double((1 - iTemp435))) + (fRec42[0] * double(iTemp435)));
			double fTemp436 = (fConst3 * (fRec115[0] * fTemp434));
			int iTemp437 = int(fTemp436);
			double fTemp438 = std::floor(fTemp436);
			double fTemp439 = (0.5 * fTemp434);
			double fTemp440 = (65536.0 * (fTemp439 - std::floor(fTemp439)));
			int iTemp441 = int(fTemp440);
			double fTemp442 = ftbl0FilDeSoi1PanStereoSIG0[iTemp441];
			double fTemp443 = (fRec114[0] + (0.5 - std::floor((fRec114[0] + 0.5))));
			fVec61[0] = fTemp443;
			int iTemp444 = ((fTemp443 > 0.001) * (fVec61[1] <= 0.001));
			fRec116[0] = ((fRec116[1] * double((1 - iTemp444))) + (fRec42[0] * double(iTemp444)));
			double fTemp445 = (fConst3 * (fRec116[0] * fTemp443));
			int iTemp446 = int(fTemp445);
			double fTemp447 = std::floor(fTemp445);
			double fTemp448 = (0.5 * fTemp443);
			double fTemp449 = (65536.0 * (fTemp448 - std::floor(fTemp448)));
			int iTemp450 = int(fTemp449);
			double fTemp451 = ftbl0FilDeSoi1PanStereoSIG0[iTemp450];
			double fTemp452 = (fRec114[0] + (0.75 - std::floor((fRec114[0] + 0.75))));
			fVec62[0] = fTemp452;
			int iTemp453 = ((fTemp452 > 0.001) * (fVec62[1] <= 0.001));
			fRec117[0] = ((fRec117[1] * double((1 - iTemp453))) + (fRec42[0] * double(iTemp453)));
			double fTemp454 = (fConst3 * (fRec117[0] * fTemp452));
			int iTemp455 = int(fTemp454);
			double fTemp456 = std::floor(fTemp454);
			double fTemp457 = (0.5 * fTemp452);
			double fTemp458 = (65536.0 * (fTemp457 - std::floor(fTemp457)));
			int iTemp459 = int(fTemp458);
			double fTemp460 = ftbl0FilDeSoi1PanStereoSIG0[iTemp459];
			fRec10[0] = (((((((fVec58[((IOTA - (iTemp428 & 262143)) & 262143)] * (fTemp429 + (1.0 - fTemp427))) + ((fTemp427 - fTemp429) * fVec58[((IOTA - ((iTemp428 + 1) & 262143)) & 262143)])) * (fTemp433 + ((fTemp431 - std::floor(fTemp431)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp432 + 1) % 65536)] - fTemp433)))) + (((fVec58[((IOTA - (iTemp437 & 262143)) & 262143)] * (fTemp438 + (1.0 - fTemp436))) + ((fTemp436 - fTemp438) * fVec58[((IOTA - ((iTemp437 + 1) & 262143)) & 262143)])) * (fTemp442 + ((fTemp440 - std::floor(fTemp440)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp441 + 1) % 65536)] - fTemp442))))) + (((fVec58[((IOTA - (iTemp446 & 262143)) & 262143)] * (fTemp447 + (1.0 - fTemp445))) + ((fTemp445 - fTemp447) * fVec58[((IOTA - ((iTemp446 + 1) & 262143)) & 262143)])) * (fTemp451 + ((fTemp449 - std::floor(fTemp449)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp450 + 1) % 65536)] - fTemp451))))) + (((fVec58[((IOTA - (iTemp455 & 262143)) & 262143)] * (fTemp456 + (1.0 - fTemp454))) + ((fTemp454 - fTemp456) * fVec58[((IOTA - ((iTemp455 + 1) & 262143)) & 262143)])) * (fTemp460 + ((fTemp458 - std::floor(fTemp458)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp459 + 1) % 65536)] - fTemp460))))) + (fSlow256 * fTemp422));
			fRec118[0] = (fSlow273 + (fSlow0 * fRec118[1]));
			double fTemp461 = (((((((((((((((((fSlow257 * fTemp5) + (fSlow258 * fTemp6)) + (fSlow259 * fTemp7)) + (fSlow260 * fTemp8)) + (fSlow261 * fTemp9)) + (fSlow262 * fTemp10)) + (fSlow263 * fTemp11)) + (fSlow264 * fTemp12)) + (fSlow265 * fTemp13)) + (fSlow266 * fTemp14)) + (fSlow267 * fTemp15)) + (fSlow268 * fTemp16)) + (fSlow269 * fTemp17)) + (fSlow270 * fTemp18)) + (fSlow271 * fTemp19)) + (fSlow272 * fTemp20)) + (((fTemp21 * fRec118[0]) * fTemp22) * fTemp23));
			fVec63[(IOTA & 1048575)] = fTemp461;
			iRec119[0] = ((iTemp27 * iRec119[1]) + (iSlow274 * iTemp26));
			iRec120[0] = ((iTemp30 * iRec120[1]) + (iSlow274 * iTemp29));
			double fTemp462 = ((0.5 * (fTemp4 * fVec63[((IOTA - (iRec119[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec63[((IOTA - (iRec120[0] & 1048575)) & 1048575)]));
			int iTemp463 = (fTemp462 > 1.0);
			int iTemp464 = (fTemp462 < -1.0);
			double fTemp465 = (double((iTemp463 - iTemp464)) + (fTemp462 * double(((1 - iTemp464) * (1 - iTemp463)))));
			double fTemp466 = (fSlow43 * fTemp465);
			fVec64[(IOTA & 262143)] = fTemp466;
			double fTemp467 = (fRec122[1] + (fSlow275 / fRec42[0]));
			fRec122[0] = (fTemp467 - std::floor(fTemp467));
			double fTemp468 = (fRec122[0] - std::floor(fRec122[0]));
			fVec65[0] = fTemp468;
			int iTemp469 = ((fTemp468 > 0.001) * (fVec65[1] <= 0.001));
			fRec121[0] = ((fRec121[1] * double((1 - iTemp469))) + (fRec42[0] * double(iTemp469)));
			double fTemp470 = (fConst3 * (fRec121[0] * fTemp468));
			int iTemp471 = int(fTemp470);
			double fTemp472 = std::floor(fTemp470);
			double fTemp473 = (0.5 * fTemp468);
			double fTemp474 = (65536.0 * (fTemp473 - std::floor(fTemp473)));
			int iTemp475 = int(fTemp474);
			double fTemp476 = ftbl0FilDeSoi1PanStereoSIG0[iTemp475];
			double fTemp477 = (fRec122[0] + (0.25 - std::floor((fRec122[0] + 0.25))));
			fVec66[0] = fTemp477;
			int iTemp478 = ((fTemp477 > 0.001) * (fVec66[1] <= 0.001));
			fRec123[0] = ((fRec123[1] * double((1 - iTemp478))) + (fRec42[0] * double(iTemp478)));
			double fTemp479 = (fConst3 * (fRec123[0] * fTemp477));
			int iTemp480 = int(fTemp479);
			double fTemp481 = std::floor(fTemp479);
			double fTemp482 = (0.5 * fTemp477);
			double fTemp483 = (65536.0 * (fTemp482 - std::floor(fTemp482)));
			int iTemp484 = int(fTemp483);
			double fTemp485 = ftbl0FilDeSoi1PanStereoSIG0[iTemp484];
			double fTemp486 = (fRec122[0] + (0.5 - std::floor((fRec122[0] + 0.5))));
			fVec67[0] = fTemp486;
			int iTemp487 = ((fTemp486 > 0.001) * (fVec67[1] <= 0.001));
			fRec124[0] = ((fRec124[1] * double((1 - iTemp487))) + (fRec42[0] * double(iTemp487)));
			double fTemp488 = (fConst3 * (fRec124[0] * fTemp486));
			int iTemp489 = int(fTemp488);
			double fTemp490 = std::floor(fTemp488);
			double fTemp491 = (0.5 * fTemp486);
			double fTemp492 = (65536.0 * (fTemp491 - std::floor(fTemp491)));
			int iTemp493 = int(fTemp492);
			double fTemp494 = ftbl0FilDeSoi1PanStereoSIG0[iTemp493];
			double fTemp495 = (fRec122[0] + (0.75 - std::floor((fRec122[0] + 0.75))));
			fVec68[0] = fTemp495;
			int iTemp496 = ((fTemp495 > 0.001) * (fVec68[1] <= 0.001));
			fRec125[0] = ((fRec125[1] * double((1 - iTemp496))) + (fRec42[0] * double(iTemp496)));
			double fTemp497 = (fConst3 * (fRec125[0] * fTemp495));
			int iTemp498 = int(fTemp497);
			double fTemp499 = std::floor(fTemp497);
			double fTemp500 = (0.5 * fTemp495);
			double fTemp501 = (65536.0 * (fTemp500 - std::floor(fTemp500)));
			int iTemp502 = int(fTemp501);
			double fTemp503 = ftbl0FilDeSoi1PanStereoSIG0[iTemp502];
			fRec11[0] = (((((((fVec64[((IOTA - (iTemp471 & 262143)) & 262143)] * (fTemp472 + (1.0 - fTemp470))) + ((fTemp470 - fTemp472) * fVec64[((IOTA - ((iTemp471 + 1) & 262143)) & 262143)])) * (fTemp476 + ((fTemp474 - std::floor(fTemp474)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp475 + 1) % 65536)] - fTemp476)))) + (((fVec64[((IOTA - (iTemp480 & 262143)) & 262143)] * (fTemp481 + (1.0 - fTemp479))) + ((fTemp479 - fTemp481) * fVec64[((IOTA - ((iTemp480 + 1) & 262143)) & 262143)])) * (fTemp485 + ((fTemp483 - std::floor(fTemp483)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp484 + 1) % 65536)] - fTemp485))))) + (((fVec64[((IOTA - (iTemp489 & 262143)) & 262143)] * (fTemp490 + (1.0 - fTemp488))) + ((fTemp488 - fTemp490) * fVec64[((IOTA - ((iTemp489 + 1) & 262143)) & 262143)])) * (fTemp494 + ((fTemp492 - std::floor(fTemp492)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp493 + 1) % 65536)] - fTemp494))))) + (((fVec64[((IOTA - (iTemp498 & 262143)) & 262143)] * (fTemp499 + (1.0 - fTemp497))) + ((fTemp497 - fTemp499) * fVec64[((IOTA - ((iTemp498 + 1) & 262143)) & 262143)])) * (fTemp503 + ((fTemp501 - std::floor(fTemp501)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp502 + 1) % 65536)] - fTemp503))))) + (fSlow276 * fTemp465));
			fRec126[0] = (fSlow293 + (fSlow0 * fRec126[1]));
			double fTemp504 = (((((((((((((((((fSlow277 * fTemp5) + (fSlow278 * fTemp6)) + (fSlow279 * fTemp7)) + (fSlow280 * fTemp8)) + (fSlow281 * fTemp9)) + (fSlow282 * fTemp10)) + (fSlow283 * fTemp11)) + (fSlow284 * fTemp12)) + (fSlow285 * fTemp13)) + (fSlow286 * fTemp14)) + (fSlow287 * fTemp15)) + (fSlow288 * fTemp16)) + (fSlow289 * fTemp17)) + (fSlow290 * fTemp18)) + (fSlow291 * fTemp19)) + (fSlow292 * fTemp20)) + (((fTemp21 * fRec126[0]) * fTemp22) * fTemp23));
			fVec69[(IOTA & 1048575)] = fTemp504;
			iRec127[0] = ((iTemp27 * iRec127[1]) + (iSlow294 * iTemp26));
			iRec128[0] = ((iTemp30 * iRec128[1]) + (iSlow294 * iTemp29));
			double fTemp505 = ((0.5 * (fTemp4 * fVec69[((IOTA - (iRec127[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec69[((IOTA - (iRec128[0] & 1048575)) & 1048575)]));
			int iTemp506 = (fTemp505 > 1.0);
			int iTemp507 = (fTemp505 < -1.0);
			double fTemp508 = (double((iTemp506 - iTemp507)) + (fTemp505 * double(((1 - iTemp507) * (1 - iTemp506)))));
			double fTemp509 = (fSlow47 * fTemp508);
			fVec70[(IOTA & 262143)] = fTemp509;
			double fTemp510 = (fRec130[1] + (fSlow295 / fRec42[0]));
			fRec130[0] = (fTemp510 - std::floor(fTemp510));
			double fTemp511 = (fRec130[0] - std::floor(fRec130[0]));
			fVec71[0] = fTemp511;
			int iTemp512 = ((fTemp511 > 0.001) * (fVec71[1] <= 0.001));
			fRec129[0] = ((fRec129[1] * double((1 - iTemp512))) + (fRec42[0] * double(iTemp512)));
			double fTemp513 = (fConst3 * (fRec129[0] * fTemp511));
			int iTemp514 = int(fTemp513);
			double fTemp515 = std::floor(fTemp513);
			double fTemp516 = (0.5 * fTemp511);
			double fTemp517 = (65536.0 * (fTemp516 - std::floor(fTemp516)));
			int iTemp518 = int(fTemp517);
			double fTemp519 = ftbl0FilDeSoi1PanStereoSIG0[iTemp518];
			double fTemp520 = (fRec130[0] + (0.25 - std::floor((fRec130[0] + 0.25))));
			fVec72[0] = fTemp520;
			int iTemp521 = ((fTemp520 > 0.001) * (fVec72[1] <= 0.001));
			fRec131[0] = ((fRec131[1] * double((1 - iTemp521))) + (fRec42[0] * double(iTemp521)));
			double fTemp522 = (fConst3 * (fRec131[0] * fTemp520));
			int iTemp523 = int(fTemp522);
			double fTemp524 = std::floor(fTemp522);
			double fTemp525 = (0.5 * fTemp520);
			double fTemp526 = (65536.0 * (fTemp525 - std::floor(fTemp525)));
			int iTemp527 = int(fTemp526);
			double fTemp528 = ftbl0FilDeSoi1PanStereoSIG0[iTemp527];
			double fTemp529 = (fRec130[0] + (0.5 - std::floor((fRec130[0] + 0.5))));
			fVec73[0] = fTemp529;
			int iTemp530 = ((fTemp529 > 0.001) * (fVec73[1] <= 0.001));
			fRec132[0] = ((fRec132[1] * double((1 - iTemp530))) + (fRec42[0] * double(iTemp530)));
			double fTemp531 = (fConst3 * (fRec132[0] * fTemp529));
			int iTemp532 = int(fTemp531);
			double fTemp533 = std::floor(fTemp531);
			double fTemp534 = (0.5 * fTemp529);
			double fTemp535 = (65536.0 * (fTemp534 - std::floor(fTemp534)));
			int iTemp536 = int(fTemp535);
			double fTemp537 = ftbl0FilDeSoi1PanStereoSIG0[iTemp536];
			double fTemp538 = (fRec130[0] + (0.75 - std::floor((fRec130[0] + 0.75))));
			fVec74[0] = fTemp538;
			int iTemp539 = ((fTemp538 > 0.001) * (fVec74[1] <= 0.001));
			fRec133[0] = ((fRec133[1] * double((1 - iTemp539))) + (fRec42[0] * double(iTemp539)));
			double fTemp540 = (fConst3 * (fRec133[0] * fTemp538));
			int iTemp541 = int(fTemp540);
			double fTemp542 = std::floor(fTemp540);
			double fTemp543 = (0.5 * fTemp538);
			double fTemp544 = (65536.0 * (fTemp543 - std::floor(fTemp543)));
			int iTemp545 = int(fTemp544);
			double fTemp546 = ftbl0FilDeSoi1PanStereoSIG0[iTemp545];
			fRec12[0] = (((((((fVec70[((IOTA - (iTemp514 & 262143)) & 262143)] * (fTemp515 + (1.0 - fTemp513))) + ((fTemp513 - fTemp515) * fVec70[((IOTA - ((iTemp514 + 1) & 262143)) & 262143)])) * (fTemp519 + ((fTemp517 - std::floor(fTemp517)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp518 + 1) % 65536)] - fTemp519)))) + (((fVec70[((IOTA - (iTemp523 & 262143)) & 262143)] * (fTemp524 + (1.0 - fTemp522))) + ((fTemp522 - fTemp524) * fVec70[((IOTA - ((iTemp523 + 1) & 262143)) & 262143)])) * (fTemp528 + ((fTemp526 - std::floor(fTemp526)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp527 + 1) % 65536)] - fTemp528))))) + (((fVec70[((IOTA - (iTemp532 & 262143)) & 262143)] * (fTemp533 + (1.0 - fTemp531))) + ((fTemp531 - fTemp533) * fVec70[((IOTA - ((iTemp532 + 1) & 262143)) & 262143)])) * (fTemp537 + ((fTemp535 - std::floor(fTemp535)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp536 + 1) % 65536)] - fTemp537))))) + (((fVec70[((IOTA - (iTemp541 & 262143)) & 262143)] * (fTemp542 + (1.0 - fTemp540))) + ((fTemp540 - fTemp542) * fVec70[((IOTA - ((iTemp541 + 1) & 262143)) & 262143)])) * (fTemp546 + ((fTemp544 - std::floor(fTemp544)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp545 + 1) % 65536)] - fTemp546))))) + (fSlow296 * fTemp508));
			fRec134[0] = (fSlow313 + (fSlow0 * fRec134[1]));
			double fTemp547 = (((((((((((((((((fSlow297 * fTemp5) + (fSlow298 * fTemp6)) + (fSlow299 * fTemp7)) + (fSlow300 * fTemp8)) + (fSlow301 * fTemp9)) + (fSlow302 * fTemp10)) + (fSlow303 * fTemp11)) + (fSlow304 * fTemp12)) + (fSlow305 * fTemp13)) + (fSlow306 * fTemp14)) + (fSlow307 * fTemp15)) + (fSlow308 * fTemp16)) + (fSlow309 * fTemp17)) + (fSlow310 * fTemp18)) + (fSlow311 * fTemp19)) + (fSlow312 * fTemp20)) + (((fTemp21 * fRec134[0]) * fTemp22) * fTemp23));
			fVec75[(IOTA & 1048575)] = fTemp547;
			iRec135[0] = ((iTemp27 * iRec135[1]) + (iSlow314 * iTemp26));
			iRec136[0] = ((iTemp30 * iRec136[1]) + (iSlow314 * iTemp29));
			double fTemp548 = ((0.5 * (fTemp4 * fVec75[((IOTA - (iRec135[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec75[((IOTA - (iRec136[0] & 1048575)) & 1048575)]));
			int iTemp549 = (fTemp548 > 1.0);
			int iTemp550 = (fTemp548 < -1.0);
			double fTemp551 = (double((iTemp549 - iTemp550)) + (fTemp548 * double(((1 - iTemp550) * (1 - iTemp549)))));
			double fTemp552 = (fSlow51 * fTemp551);
			fVec76[(IOTA & 262143)] = fTemp552;
			double fTemp553 = (fRec138[1] + (fSlow315 / fRec42[0]));
			fRec138[0] = (fTemp553 - std::floor(fTemp553));
			double fTemp554 = (fRec138[0] - std::floor(fRec138[0]));
			fVec77[0] = fTemp554;
			int iTemp555 = ((fTemp554 > 0.001) * (fVec77[1] <= 0.001));
			fRec137[0] = ((fRec137[1] * double((1 - iTemp555))) + (fRec42[0] * double(iTemp555)));
			double fTemp556 = (fConst3 * (fRec137[0] * fTemp554));
			int iTemp557 = int(fTemp556);
			double fTemp558 = std::floor(fTemp556);
			double fTemp559 = (0.5 * fTemp554);
			double fTemp560 = (65536.0 * (fTemp559 - std::floor(fTemp559)));
			int iTemp561 = int(fTemp560);
			double fTemp562 = ftbl0FilDeSoi1PanStereoSIG0[iTemp561];
			double fTemp563 = (fRec138[0] + (0.25 - std::floor((fRec138[0] + 0.25))));
			fVec78[0] = fTemp563;
			int iTemp564 = ((fTemp563 > 0.001) * (fVec78[1] <= 0.001));
			fRec139[0] = ((fRec139[1] * double((1 - iTemp564))) + (fRec42[0] * double(iTemp564)));
			double fTemp565 = (fConst3 * (fRec139[0] * fTemp563));
			int iTemp566 = int(fTemp565);
			double fTemp567 = std::floor(fTemp565);
			double fTemp568 = (0.5 * fTemp563);
			double fTemp569 = (65536.0 * (fTemp568 - std::floor(fTemp568)));
			int iTemp570 = int(fTemp569);
			double fTemp571 = ftbl0FilDeSoi1PanStereoSIG0[iTemp570];
			double fTemp572 = (fRec138[0] + (0.5 - std::floor((fRec138[0] + 0.5))));
			fVec79[0] = fTemp572;
			int iTemp573 = ((fTemp572 > 0.001) * (fVec79[1] <= 0.001));
			fRec140[0] = ((fRec140[1] * double((1 - iTemp573))) + (fRec42[0] * double(iTemp573)));
			double fTemp574 = (fConst3 * (fRec140[0] * fTemp572));
			int iTemp575 = int(fTemp574);
			double fTemp576 = std::floor(fTemp574);
			double fTemp577 = (0.5 * fTemp572);
			double fTemp578 = (65536.0 * (fTemp577 - std::floor(fTemp577)));
			int iTemp579 = int(fTemp578);
			double fTemp580 = ftbl0FilDeSoi1PanStereoSIG0[iTemp579];
			double fTemp581 = (fRec138[0] + (0.75 - std::floor((fRec138[0] + 0.75))));
			fVec80[0] = fTemp581;
			int iTemp582 = ((fTemp581 > 0.001) * (fVec80[1] <= 0.001));
			fRec141[0] = ((fRec141[1] * double((1 - iTemp582))) + (fRec42[0] * double(iTemp582)));
			double fTemp583 = (fConst3 * (fRec141[0] * fTemp581));
			int iTemp584 = int(fTemp583);
			double fTemp585 = std::floor(fTemp583);
			double fTemp586 = (0.5 * fTemp581);
			double fTemp587 = (65536.0 * (fTemp586 - std::floor(fTemp586)));
			int iTemp588 = int(fTemp587);
			double fTemp589 = ftbl0FilDeSoi1PanStereoSIG0[iTemp588];
			fRec13[0] = (((((((fVec76[((IOTA - (iTemp557 & 262143)) & 262143)] * (fTemp558 + (1.0 - fTemp556))) + ((fTemp556 - fTemp558) * fVec76[((IOTA - ((iTemp557 + 1) & 262143)) & 262143)])) * (fTemp562 + ((fTemp560 - std::floor(fTemp560)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp561 + 1) % 65536)] - fTemp562)))) + (((fVec76[((IOTA - (iTemp566 & 262143)) & 262143)] * (fTemp567 + (1.0 - fTemp565))) + ((fTemp565 - fTemp567) * fVec76[((IOTA - ((iTemp566 + 1) & 262143)) & 262143)])) * (fTemp571 + ((fTemp569 - std::floor(fTemp569)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp570 + 1) % 65536)] - fTemp571))))) + (((fVec76[((IOTA - (iTemp575 & 262143)) & 262143)] * (fTemp576 + (1.0 - fTemp574))) + ((fTemp574 - fTemp576) * fVec76[((IOTA - ((iTemp575 + 1) & 262143)) & 262143)])) * (fTemp580 + ((fTemp578 - std::floor(fTemp578)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp579 + 1) % 65536)] - fTemp580))))) + (((fVec76[((IOTA - (iTemp584 & 262143)) & 262143)] * (fTemp585 + (1.0 - fTemp583))) + ((fTemp583 - fTemp585) * fVec76[((IOTA - ((iTemp584 + 1) & 262143)) & 262143)])) * (fTemp589 + ((fTemp587 - std::floor(fTemp587)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp588 + 1) % 65536)] - fTemp589))))) + (fSlow316 * fTemp551));
			fRec142[0] = (fSlow333 + (fSlow0 * fRec142[1]));
			double fTemp590 = (((((((((((((((((fSlow317 * fTemp5) + (fSlow318 * fTemp6)) + (fSlow319 * fTemp7)) + (fSlow320 * fTemp8)) + (fSlow321 * fTemp9)) + (fSlow322 * fTemp10)) + (fSlow323 * fTemp11)) + (fSlow324 * fTemp12)) + (fSlow325 * fTemp13)) + (fSlow326 * fTemp14)) + (fSlow327 * fTemp15)) + (fSlow328 * fTemp16)) + (fSlow329 * fTemp17)) + (fSlow330 * fTemp18)) + (fSlow331 * fTemp19)) + (fSlow332 * fTemp20)) + (((fTemp21 * fRec142[0]) * fTemp22) * fTemp23));
			fVec81[(IOTA & 1048575)] = fTemp590;
			iRec143[0] = ((iTemp27 * iRec143[1]) + (iSlow334 * iTemp26));
			iRec144[0] = ((iTemp30 * iRec144[1]) + (iSlow334 * iTemp29));
			double fTemp591 = ((0.5 * (fTemp4 * fVec81[((IOTA - (iRec143[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec81[((IOTA - (iRec144[0] & 1048575)) & 1048575)]));
			int iTemp592 = (fTemp591 > 1.0);
			int iTemp593 = (fTemp591 < -1.0);
			double fTemp594 = (double((iTemp592 - iTemp593)) + (fTemp591 * double(((1 - iTemp593) * (1 - iTemp592)))));
			double fTemp595 = (fSlow55 * fTemp594);
			fVec82[(IOTA & 262143)] = fTemp595;
			double fTemp596 = (fRec146[1] + (fSlow335 / fRec42[0]));
			fRec146[0] = (fTemp596 - std::floor(fTemp596));
			double fTemp597 = (fRec146[0] - std::floor(fRec146[0]));
			fVec83[0] = fTemp597;
			int iTemp598 = ((fTemp597 > 0.001) * (fVec83[1] <= 0.001));
			fRec145[0] = ((fRec145[1] * double((1 - iTemp598))) + (fRec42[0] * double(iTemp598)));
			double fTemp599 = (fConst3 * (fRec145[0] * fTemp597));
			int iTemp600 = int(fTemp599);
			double fTemp601 = std::floor(fTemp599);
			double fTemp602 = (0.5 * fTemp597);
			double fTemp603 = (65536.0 * (fTemp602 - std::floor(fTemp602)));
			int iTemp604 = int(fTemp603);
			double fTemp605 = ftbl0FilDeSoi1PanStereoSIG0[iTemp604];
			double fTemp606 = (fRec146[0] + (0.25 - std::floor((fRec146[0] + 0.25))));
			fVec84[0] = fTemp606;
			int iTemp607 = ((fTemp606 > 0.001) * (fVec84[1] <= 0.001));
			fRec147[0] = ((fRec147[1] * double((1 - iTemp607))) + (fRec42[0] * double(iTemp607)));
			double fTemp608 = (fConst3 * (fRec147[0] * fTemp606));
			int iTemp609 = int(fTemp608);
			double fTemp610 = std::floor(fTemp608);
			double fTemp611 = (0.5 * fTemp606);
			double fTemp612 = (65536.0 * (fTemp611 - std::floor(fTemp611)));
			int iTemp613 = int(fTemp612);
			double fTemp614 = ftbl0FilDeSoi1PanStereoSIG0[iTemp613];
			double fTemp615 = (fRec146[0] + (0.5 - std::floor((fRec146[0] + 0.5))));
			fVec85[0] = fTemp615;
			int iTemp616 = ((fTemp615 > 0.001) * (fVec85[1] <= 0.001));
			fRec148[0] = ((fRec148[1] * double((1 - iTemp616))) + (fRec42[0] * double(iTemp616)));
			double fTemp617 = (fConst3 * (fRec148[0] * fTemp615));
			int iTemp618 = int(fTemp617);
			double fTemp619 = std::floor(fTemp617);
			double fTemp620 = (0.5 * fTemp615);
			double fTemp621 = (65536.0 * (fTemp620 - std::floor(fTemp620)));
			int iTemp622 = int(fTemp621);
			double fTemp623 = ftbl0FilDeSoi1PanStereoSIG0[iTemp622];
			double fTemp624 = (fRec146[0] + (0.75 - std::floor((fRec146[0] + 0.75))));
			fVec86[0] = fTemp624;
			int iTemp625 = ((fTemp624 > 0.001) * (fVec86[1] <= 0.001));
			fRec149[0] = ((fRec149[1] * double((1 - iTemp625))) + (fRec42[0] * double(iTemp625)));
			double fTemp626 = (fConst3 * (fRec149[0] * fTemp624));
			int iTemp627 = int(fTemp626);
			double fTemp628 = std::floor(fTemp626);
			double fTemp629 = (0.5 * fTemp624);
			double fTemp630 = (65536.0 * (fTemp629 - std::floor(fTemp629)));
			int iTemp631 = int(fTemp630);
			double fTemp632 = ftbl0FilDeSoi1PanStereoSIG0[iTemp631];
			fRec14[0] = (((((((fVec82[((IOTA - (iTemp600 & 262143)) & 262143)] * (fTemp601 + (1.0 - fTemp599))) + ((fTemp599 - fTemp601) * fVec82[((IOTA - ((iTemp600 + 1) & 262143)) & 262143)])) * (fTemp605 + ((fTemp603 - std::floor(fTemp603)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp604 + 1) % 65536)] - fTemp605)))) + (((fVec82[((IOTA - (iTemp609 & 262143)) & 262143)] * (fTemp610 + (1.0 - fTemp608))) + ((fTemp608 - fTemp610) * fVec82[((IOTA - ((iTemp609 + 1) & 262143)) & 262143)])) * (fTemp614 + ((fTemp612 - std::floor(fTemp612)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp613 + 1) % 65536)] - fTemp614))))) + (((fVec82[((IOTA - (iTemp618 & 262143)) & 262143)] * (fTemp619 + (1.0 - fTemp617))) + ((fTemp617 - fTemp619) * fVec82[((IOTA - ((iTemp618 + 1) & 262143)) & 262143)])) * (fTemp623 + ((fTemp621 - std::floor(fTemp621)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp622 + 1) % 65536)] - fTemp623))))) + (((fVec82[((IOTA - (iTemp627 & 262143)) & 262143)] * (fTemp628 + (1.0 - fTemp626))) + ((fTemp626 - fTemp628) * fVec82[((IOTA - ((iTemp627 + 1) & 262143)) & 262143)])) * (fTemp632 + ((fTemp630 - std::floor(fTemp630)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp631 + 1) % 65536)] - fTemp632))))) + (fSlow336 * fTemp594));
			fRec150[0] = (fSlow353 + (fSlow0 * fRec150[1]));
			double fTemp633 = (((((((((((((((((fSlow337 * fTemp5) + (fSlow338 * fTemp6)) + (fSlow339 * fTemp7)) + (fSlow340 * fTemp8)) + (fSlow341 * fTemp9)) + (fSlow342 * fTemp10)) + (fSlow343 * fTemp11)) + (fSlow344 * fTemp12)) + (fSlow345 * fTemp13)) + (fSlow346 * fTemp14)) + (fSlow347 * fTemp15)) + (fSlow348 * fTemp16)) + (fSlow349 * fTemp17)) + (fSlow350 * fTemp18)) + (fSlow351 * fTemp19)) + (fSlow352 * fTemp20)) + (((fTemp21 * fRec150[0]) * fTemp22) * fTemp23));
			fVec87[(IOTA & 1048575)] = fTemp633;
			iRec151[0] = ((iTemp27 * iRec151[1]) + (iSlow354 * iTemp26));
			iRec152[0] = ((iTemp30 * iRec152[1]) + (iSlow354 * iTemp29));
			double fTemp634 = ((0.5 * (fTemp4 * fVec87[((IOTA - (iRec151[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec87[((IOTA - (iRec152[0] & 1048575)) & 1048575)]));
			int iTemp635 = (fTemp634 > 1.0);
			int iTemp636 = (fTemp634 < -1.0);
			double fTemp637 = (double((iTemp635 - iTemp636)) + (fTemp634 * double(((1 - iTemp636) * (1 - iTemp635)))));
			double fTemp638 = (fSlow59 * fTemp637);
			fVec88[(IOTA & 262143)] = fTemp638;
			double fTemp639 = (fRec154[1] + (fSlow355 / fRec42[0]));
			fRec154[0] = (fTemp639 - std::floor(fTemp639));
			double fTemp640 = (fRec154[0] - std::floor(fRec154[0]));
			fVec89[0] = fTemp640;
			int iTemp641 = ((fTemp640 > 0.001) * (fVec89[1] <= 0.001));
			fRec153[0] = ((fRec153[1] * double((1 - iTemp641))) + (fRec42[0] * double(iTemp641)));
			double fTemp642 = (fConst3 * (fRec153[0] * fTemp640));
			int iTemp643 = int(fTemp642);
			double fTemp644 = std::floor(fTemp642);
			double fTemp645 = (0.5 * fTemp640);
			double fTemp646 = (65536.0 * (fTemp645 - std::floor(fTemp645)));
			int iTemp647 = int(fTemp646);
			double fTemp648 = ftbl0FilDeSoi1PanStereoSIG0[iTemp647];
			double fTemp649 = (fRec154[0] + (0.25 - std::floor((fRec154[0] + 0.25))));
			fVec90[0] = fTemp649;
			int iTemp650 = ((fTemp649 > 0.001) * (fVec90[1] <= 0.001));
			fRec155[0] = ((fRec155[1] * double((1 - iTemp650))) + (fRec42[0] * double(iTemp650)));
			double fTemp651 = (fConst3 * (fRec155[0] * fTemp649));
			int iTemp652 = int(fTemp651);
			double fTemp653 = std::floor(fTemp651);
			double fTemp654 = (0.5 * fTemp649);
			double fTemp655 = (65536.0 * (fTemp654 - std::floor(fTemp654)));
			int iTemp656 = int(fTemp655);
			double fTemp657 = ftbl0FilDeSoi1PanStereoSIG0[iTemp656];
			double fTemp658 = (fRec154[0] + (0.5 - std::floor((fRec154[0] + 0.5))));
			fVec91[0] = fTemp658;
			int iTemp659 = ((fTemp658 > 0.001) * (fVec91[1] <= 0.001));
			fRec156[0] = ((fRec156[1] * double((1 - iTemp659))) + (fRec42[0] * double(iTemp659)));
			double fTemp660 = (fConst3 * (fRec156[0] * fTemp658));
			int iTemp661 = int(fTemp660);
			double fTemp662 = std::floor(fTemp660);
			double fTemp663 = (0.5 * fTemp658);
			double fTemp664 = (65536.0 * (fTemp663 - std::floor(fTemp663)));
			int iTemp665 = int(fTemp664);
			double fTemp666 = ftbl0FilDeSoi1PanStereoSIG0[iTemp665];
			double fTemp667 = (fRec154[0] + (0.75 - std::floor((fRec154[0] + 0.75))));
			fVec92[0] = fTemp667;
			int iTemp668 = ((fTemp667 > 0.001) * (fVec92[1] <= 0.001));
			fRec157[0] = ((fRec157[1] * double((1 - iTemp668))) + (fRec42[0] * double(iTemp668)));
			double fTemp669 = (fConst3 * (fRec157[0] * fTemp667));
			int iTemp670 = int(fTemp669);
			double fTemp671 = std::floor(fTemp669);
			double fTemp672 = (0.5 * fTemp667);
			double fTemp673 = (65536.0 * (fTemp672 - std::floor(fTemp672)));
			int iTemp674 = int(fTemp673);
			double fTemp675 = ftbl0FilDeSoi1PanStereoSIG0[iTemp674];
			fRec15[0] = (((((((fVec88[((IOTA - (iTemp643 & 262143)) & 262143)] * (fTemp644 + (1.0 - fTemp642))) + ((fTemp642 - fTemp644) * fVec88[((IOTA - ((iTemp643 + 1) & 262143)) & 262143)])) * (fTemp648 + ((fTemp646 - std::floor(fTemp646)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp647 + 1) % 65536)] - fTemp648)))) + (((fVec88[((IOTA - (iTemp652 & 262143)) & 262143)] * (fTemp653 + (1.0 - fTemp651))) + ((fTemp651 - fTemp653) * fVec88[((IOTA - ((iTemp652 + 1) & 262143)) & 262143)])) * (fTemp657 + ((fTemp655 - std::floor(fTemp655)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp656 + 1) % 65536)] - fTemp657))))) + (((fVec88[((IOTA - (iTemp661 & 262143)) & 262143)] * (fTemp662 + (1.0 - fTemp660))) + ((fTemp660 - fTemp662) * fVec88[((IOTA - ((iTemp661 + 1) & 262143)) & 262143)])) * (fTemp666 + ((fTemp664 - std::floor(fTemp664)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp665 + 1) % 65536)] - fTemp666))))) + (((fVec88[((IOTA - (iTemp670 & 262143)) & 262143)] * (fTemp671 + (1.0 - fTemp669))) + ((fTemp669 - fTemp671) * fVec88[((IOTA - ((iTemp670 + 1) & 262143)) & 262143)])) * (fTemp675 + ((fTemp673 - std::floor(fTemp673)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp674 + 1) % 65536)] - fTemp675))))) + (fSlow356 * fTemp637));
			fRec158[0] = (fSlow373 + (fSlow0 * fRec158[1]));
			double fTemp676 = (((((((((((((((((fSlow357 * fTemp5) + (fSlow358 * fTemp6)) + (fSlow359 * fTemp7)) + (fSlow360 * fTemp8)) + (fSlow361 * fTemp9)) + (fSlow362 * fTemp10)) + (fSlow363 * fTemp11)) + (fSlow364 * fTemp12)) + (fSlow365 * fTemp13)) + (fSlow366 * fTemp14)) + (fSlow367 * fTemp15)) + (fSlow368 * fTemp16)) + (fSlow369 * fTemp17)) + (fSlow370 * fTemp18)) + (fSlow371 * fTemp19)) + (fSlow372 * fTemp20)) + (((fTemp21 * fRec158[0]) * fTemp22) * fTemp23));
			fVec93[(IOTA & 1048575)] = fTemp676;
			iRec159[0] = ((iTemp27 * iRec159[1]) + (iSlow374 * iTemp26));
			iRec160[0] = ((iTemp30 * iRec160[1]) + (iSlow374 * iTemp29));
			double fTemp677 = ((0.5 * (fTemp4 * fVec93[((IOTA - (iRec159[0] & 1048575)) & 1048575)])) + (fTemp28 * fVec93[((IOTA - (iRec160[0] & 1048575)) & 1048575)]));
			int iTemp678 = (fTemp677 > 1.0);
			int iTemp679 = (fTemp677 < -1.0);
			double fTemp680 = (double((iTemp678 - iTemp679)) + (fTemp677 * double(((1 - iTemp679) * (1 - iTemp678)))));
			double fTemp681 = (fSlow63 * fTemp680);
			fVec94[(IOTA & 262143)] = fTemp681;
			double fTemp682 = (fRec162[1] + (fSlow375 / fRec42[0]));
			fRec162[0] = (fTemp682 - std::floor(fTemp682));
			double fTemp683 = (fRec162[0] - std::floor(fRec162[0]));
			fVec95[0] = fTemp683;
			int iTemp684 = ((fTemp683 > 0.001) * (fVec95[1] <= 0.001));
			fRec161[0] = ((fRec161[1] * double((1 - iTemp684))) + (fRec42[0] * double(iTemp684)));
			double fTemp685 = (fConst3 * (fRec161[0] * fTemp683));
			int iTemp686 = int(fTemp685);
			double fTemp687 = std::floor(fTemp685);
			double fTemp688 = (0.5 * fTemp683);
			double fTemp689 = (65536.0 * (fTemp688 - std::floor(fTemp688)));
			int iTemp690 = int(fTemp689);
			double fTemp691 = ftbl0FilDeSoi1PanStereoSIG0[iTemp690];
			double fTemp692 = (fRec162[0] + (0.25 - std::floor((fRec162[0] + 0.25))));
			fVec96[0] = fTemp692;
			int iTemp693 = ((fTemp692 > 0.001) * (fVec96[1] <= 0.001));
			fRec163[0] = ((fRec163[1] * double((1 - iTemp693))) + (fRec42[0] * double(iTemp693)));
			double fTemp694 = (fConst3 * (fRec163[0] * fTemp692));
			int iTemp695 = int(fTemp694);
			double fTemp696 = std::floor(fTemp694);
			double fTemp697 = (0.5 * fTemp692);
			double fTemp698 = (65536.0 * (fTemp697 - std::floor(fTemp697)));
			int iTemp699 = int(fTemp698);
			double fTemp700 = ftbl0FilDeSoi1PanStereoSIG0[iTemp699];
			double fTemp701 = (fRec162[0] + (0.5 - std::floor((fRec162[0] + 0.5))));
			fVec97[0] = fTemp701;
			int iTemp702 = ((fTemp701 > 0.001) * (fVec97[1] <= 0.001));
			fRec164[0] = ((fRec164[1] * double((1 - iTemp702))) + (fRec42[0] * double(iTemp702)));
			double fTemp703 = (fConst3 * (fRec164[0] * fTemp701));
			int iTemp704 = int(fTemp703);
			double fTemp705 = std::floor(fTemp703);
			double fTemp706 = (0.5 * fTemp701);
			double fTemp707 = (65536.0 * (fTemp706 - std::floor(fTemp706)));
			int iTemp708 = int(fTemp707);
			double fTemp709 = ftbl0FilDeSoi1PanStereoSIG0[iTemp708];
			double fTemp710 = (fRec162[0] + (0.75 - std::floor((fRec162[0] + 0.75))));
			fVec98[0] = fTemp710;
			int iTemp711 = ((fTemp710 > 0.001) * (fVec98[1] <= 0.001));
			fRec165[0] = ((fRec165[1] * double((1 - iTemp711))) + (fRec42[0] * double(iTemp711)));
			double fTemp712 = (fConst3 * (fRec165[0] * fTemp710));
			int iTemp713 = int(fTemp712);
			double fTemp714 = std::floor(fTemp712);
			double fTemp715 = (0.5 * fTemp710);
			double fTemp716 = (65536.0 * (fTemp715 - std::floor(fTemp715)));
			int iTemp717 = int(fTemp716);
			double fTemp718 = ftbl0FilDeSoi1PanStereoSIG0[iTemp717];
			fRec16[0] = (((((((fVec94[((IOTA - (iTemp686 & 262143)) & 262143)] * (fTemp687 + (1.0 - fTemp685))) + ((fTemp685 - fTemp687) * fVec94[((IOTA - ((iTemp686 + 1) & 262143)) & 262143)])) * (fTemp691 + ((fTemp689 - std::floor(fTemp689)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp690 + 1) % 65536)] - fTemp691)))) + (((fVec94[((IOTA - (iTemp695 & 262143)) & 262143)] * (fTemp696 + (1.0 - fTemp694))) + ((fTemp694 - fTemp696) * fVec94[((IOTA - ((iTemp695 + 1) & 262143)) & 262143)])) * (fTemp700 + ((fTemp698 - std::floor(fTemp698)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp699 + 1) % 65536)] - fTemp700))))) + (((fVec94[((IOTA - (iTemp704 & 262143)) & 262143)] * (fTemp705 + (1.0 - fTemp703))) + ((fTemp703 - fTemp705) * fVec94[((IOTA - ((iTemp704 + 1) & 262143)) & 262143)])) * (fTemp709 + ((fTemp707 - std::floor(fTemp707)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp708 + 1) % 65536)] - fTemp709))))) + (((fVec94[((IOTA - (iTemp713 & 262143)) & 262143)] * (fTemp714 + (1.0 - fTemp712))) + ((fTemp712 - fTemp714) * fVec94[((IOTA - ((iTemp713 + 1) & 262143)) & 262143)])) * (fTemp718 + ((fTemp716 - std::floor(fTemp716)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp717 + 1) % 65536)] - fTemp718))))) + (fSlow376 * fTemp680));
			fRec166[0] = (fSlow377 + (fSlow0 * fRec166[1]));
			double fTemp719 = (fRec16[0] * fRec166[0]);
			fRec167[0] = (fSlow378 + (fConst6 * fRec167[1]));
			fRec168[0] = (fSlow379 + (fConst6 * fRec168[1]));
			fRec169[0] = (fSlow380 + (fConst6 * fRec169[1]));
			fRec170[0] = (fSlow381 + (fConst6 * fRec170[1]));
			fRec171[0] = (fSlow382 + (fConst6 * fRec171[1]));
			fRec172[0] = (fSlow383 + (fSlow0 * fRec172[1]));
			double fTemp720 = (fRec15[0] * fRec172[0]);
			fRec173[0] = (fSlow384 + (fConst6 * fRec173[1]));
			fRec174[0] = (fSlow385 + (fConst6 * fRec174[1]));
			fRec175[0] = (fSlow386 + (fConst6 * fRec175[1]));
			fRec176[0] = (fSlow387 + (fConst6 * fRec176[1]));
			fRec177[0] = (fSlow388 + (fConst6 * fRec177[1]));
			fRec178[0] = (fSlow389 + (fSlow0 * fRec178[1]));
			double fTemp721 = (fRec14[0] * fRec178[0]);
			fRec179[0] = (fSlow390 + (fConst6 * fRec179[1]));
			fRec180[0] = (fSlow391 + (fConst6 * fRec180[1]));
			fRec181[0] = (fSlow392 + (fConst6 * fRec181[1]));
			fRec182[0] = (fSlow393 + (fConst6 * fRec182[1]));
			fRec183[0] = (fSlow394 + (fConst6 * fRec183[1]));
			fRec184[0] = (fSlow395 + (fSlow0 * fRec184[1]));
			double fTemp722 = (fRec13[0] * fRec184[0]);
			fRec185[0] = (fSlow396 + (fConst6 * fRec185[1]));
			fRec186[0] = (fSlow397 + (fConst6 * fRec186[1]));
			fRec187[0] = (fSlow398 + (fConst6 * fRec187[1]));
			fRec188[0] = (fSlow399 + (fConst6 * fRec188[1]));
			fRec189[0] = (fSlow400 + (fConst6 * fRec189[1]));
			fRec190[0] = (fSlow401 + (fSlow0 * fRec190[1]));
			double fTemp723 = (fRec12[0] * fRec190[0]);
			fRec191[0] = (fSlow402 + (fConst6 * fRec191[1]));
			fRec192[0] = (fSlow403 + (fConst6 * fRec192[1]));
			fRec193[0] = (fSlow404 + (fConst6 * fRec193[1]));
			fRec194[0] = (fSlow405 + (fConst6 * fRec194[1]));
			fRec195[0] = (fSlow406 + (fConst6 * fRec195[1]));
			fRec196[0] = (fSlow407 + (fSlow0 * fRec196[1]));
			double fTemp724 = (fRec11[0] * fRec196[0]);
			fRec197[0] = (fSlow408 + (fConst6 * fRec197[1]));
			fRec198[0] = (fSlow409 + (fConst6 * fRec198[1]));
			fRec199[0] = (fSlow410 + (fConst6 * fRec199[1]));
			fRec200[0] = (fSlow411 + (fConst6 * fRec200[1]));
			fRec201[0] = (fSlow412 + (fConst6 * fRec201[1]));
			fRec202[0] = (fSlow413 + (fSlow0 * fRec202[1]));
			double fTemp725 = (fRec10[0] * fRec202[0]);
			fRec203[0] = (fSlow414 + (fConst6 * fRec203[1]));
			fRec204[0] = (fSlow415 + (fConst6 * fRec204[1]));
			fRec205[0] = (fSlow416 + (fConst6 * fRec205[1]));
			fRec206[0] = (fSlow417 + (fConst6 * fRec206[1]));
			fRec207[0] = (fSlow418 + (fConst6 * fRec207[1]));
			fRec208[0] = (fSlow419 + (fSlow0 * fRec208[1]));
			double fTemp726 = (fRec9[0] * fRec208[0]);
			fRec209[0] = (fSlow420 + (fConst6 * fRec209[1]));
			fRec210[0] = (fSlow421 + (fConst6 * fRec210[1]));
			fRec211[0] = (fSlow422 + (fConst6 * fRec211[1]));
			fRec212[0] = (fSlow423 + (fConst6 * fRec212[1]));
			fRec213[0] = (fSlow424 + (fConst6 * fRec213[1]));
			fRec214[0] = (fSlow425 + (fSlow0 * fRec214[1]));
			double fTemp727 = (fRec8[0] * fRec214[0]);
			fRec215[0] = (fSlow426 + (fConst6 * fRec215[1]));
			fRec216[0] = (fSlow427 + (fConst6 * fRec216[1]));
			fRec217[0] = (fSlow428 + (fConst6 * fRec217[1]));
			fRec218[0] = (fSlow429 + (fConst6 * fRec218[1]));
			fRec219[0] = (fSlow430 + (fConst6 * fRec219[1]));
			fRec220[0] = (fSlow431 + (fSlow0 * fRec220[1]));
			double fTemp728 = (fRec7[0] * fRec220[0]);
			fRec221[0] = (fSlow432 + (fConst6 * fRec221[1]));
			fRec222[0] = (fSlow433 + (fConst6 * fRec222[1]));
			fRec223[0] = (fSlow434 + (fConst6 * fRec223[1]));
			fRec224[0] = (fSlow435 + (fConst6 * fRec224[1]));
			fRec225[0] = (fSlow436 + (fConst6 * fRec225[1]));
			fRec226[0] = (fSlow437 + (fSlow0 * fRec226[1]));
			double fTemp729 = (fRec6[0] * fRec226[0]);
			fRec227[0] = (fSlow438 + (fConst6 * fRec227[1]));
			fRec228[0] = (fSlow439 + (fConst6 * fRec228[1]));
			fRec229[0] = (fSlow440 + (fConst6 * fRec229[1]));
			fRec230[0] = (fSlow441 + (fConst6 * fRec230[1]));
			fRec231[0] = (fSlow442 + (fConst6 * fRec231[1]));
			fRec232[0] = (fSlow443 + (fSlow0 * fRec232[1]));
			double fTemp730 = (fRec5[0] * fRec232[0]);
			fRec233[0] = (fSlow444 + (fConst6 * fRec233[1]));
			fRec234[0] = (fSlow445 + (fConst6 * fRec234[1]));
			fRec235[0] = (fSlow446 + (fConst6 * fRec235[1]));
			fRec236[0] = (fSlow447 + (fConst6 * fRec236[1]));
			fRec237[0] = (fSlow448 + (fConst6 * fRec237[1]));
			fRec238[0] = (fSlow449 + (fSlow0 * fRec238[1]));
			double fTemp731 = (fRec4[0] * fRec238[0]);
			fRec239[0] = (fSlow450 + (fConst6 * fRec239[1]));
			fRec240[0] = (fSlow451 + (fConst6 * fRec240[1]));
			fRec241[0] = (fSlow452 + (fConst6 * fRec241[1]));
			fRec242[0] = (fSlow453 + (fConst6 * fRec242[1]));
			fRec243[0] = (fSlow454 + (fConst6 * fRec243[1]));
			fRec244[0] = (fSlow455 + (fSlow0 * fRec244[1]));
			double fTemp732 = (fRec3[0] * fRec244[0]);
			fRec245[0] = (fSlow456 + (fConst6 * fRec245[1]));
			fRec246[0] = (fSlow457 + (fConst6 * fRec246[1]));
			fRec247[0] = (fSlow458 + (fConst6 * fRec247[1]));
			fRec248[0] = (fSlow459 + (fConst6 * fRec248[1]));
			fRec249[0] = (fSlow460 + (fConst6 * fRec249[1]));
			fRec250[0] = (fSlow461 + (fSlow0 * fRec250[1]));
			double fTemp733 = (fRec2[0] * fRec250[0]);
			fRec251[0] = (fSlow462 + (fConst6 * fRec251[1]));
			fRec252[0] = (fSlow463 + (fConst6 * fRec252[1]));
			fRec253[0] = (fSlow464 + (fConst6 * fRec253[1]));
			fRec254[0] = (fSlow465 + (fConst6 * fRec254[1]));
			fRec255[0] = (fSlow466 + (fConst6 * fRec255[1]));
			fRec256[0] = (fSlow467 + (fSlow0 * fRec256[1]));
			double fTemp734 = double((fRec256[0] > -127.0));
			double fTemp735 = std::pow(10.0, (0.050000000000000003 * fRec256[0]));
			fRec257[0] = (fSlow468 + (fConst6 * fRec257[1]));
			fRec258[0] = (fSlow469 + (fConst6 * fRec258[1]));
			fRec259[0] = (fSlow470 + (fConst6 * fRec259[1]));
			fRec260[0] = (fSlow471 + (fConst6 * fRec260[1]));
			fRec261[0] = (fSlow472 + (fConst6 * fRec261[1]));
			fRec262[0] = (fSlow473 + (fSlow0 * fRec262[1]));
			double fTemp736 = (fRec1[0] * fRec262[0]);
			fRec263[0] = (fSlow474 + (fConst6 * fRec263[1]));
			fRec264[0] = (fSlow475 + (fConst6 * fRec264[1]));
			fRec265[0] = (fSlow476 + (fConst6 * fRec265[1]));
			fRec266[0] = (fSlow477 + (fConst6 * fRec266[1]));
			fRec267[0] = (fSlow478 + (fConst6 * fRec267[1]));
			double fTemp737 = (0.14285714285714285 * ((fTemp719 * (fRec167[0] + (fRec168[0] + (fRec169[0] + (fRec170[0] + fRec171[0]))))) + ((fTemp720 * (fRec173[0] + (fRec174[0] + (fRec175[0] + (fRec176[0] + fRec177[0]))))) + ((fTemp721 * (fRec179[0] + (fRec180[0] + (fRec181[0] + (fRec182[0] + fRec183[0]))))) + ((fTemp722 * (fRec185[0] + (fRec186[0] + (fRec187[0] + (fRec188[0] + fRec189[0]))))) + ((fTemp723 * (fRec191[0] + (fRec192[0] + (fRec193[0] + (fRec194[0] + fRec195[0]))))) + ((fTemp724 * (fRec197[0] + (fRec198[0] + (fRec199[0] + (fRec200[0] + fRec201[0]))))) + ((fTemp725 * (fRec203[0] + (fRec204[0] + (fRec205[0] + (fRec206[0] + fRec207[0]))))) + ((fTemp726 * (fRec209[0] + (fRec210[0] + (fRec211[0] + (fRec212[0] + fRec213[0]))))) + ((fTemp727 * (fRec215[0] + (fRec216[0] + (fRec217[0] + (fRec218[0] + fRec219[0]))))) + ((fTemp728 * (fRec221[0] + (fRec222[0] + (fRec223[0] + (fRec224[0] + fRec225[0]))))) + ((fTemp729 * (fRec227[0] + (fRec228[0] + (fRec229[0] + (fRec230[0] + fRec231[0]))))) + ((fTemp730 * (fRec233[0] + (fRec234[0] + (fRec235[0] + (fRec236[0] + fRec237[0]))))) + ((fTemp731 * (fRec239[0] + (fRec240[0] + (fRec241[0] + (fRec242[0] + fRec243[0]))))) + ((fTemp732 * (fRec245[0] + (fRec246[0] + (fRec247[0] + (fRec248[0] + fRec249[0]))))) + ((fTemp733 * (fRec251[0] + (fRec252[0] + (fRec253[0] + (fRec254[0] + fRec255[0]))))) + ((((fTemp21 * fTemp734) * fTemp735) * (fRec257[0] + (fRec258[0] + (fRec259[0] + (fRec260[0] + fRec261[0]))))) + (fTemp736 * (fRec263[0] + (fRec264[0] + (fRec265[0] + (fRec266[0] + fRec267[0]))))))))))))))))))))));
			fRec268[0] = (fSlow482 + (fConst6 * fRec268[1]));
			fRec269[0] = (fSlow483 + (fSlow0 * fRec269[1]));
			double fTemp738 = double((fRec269[0] > -127.0));
			fRec271[0] = (fSlow484 + (fRec271[1] - std::floor((fSlow484 + fRec271[1]))));
			int iTemp739 = ((fRec271[0] > 0.001) * (fRec271[1] <= 0.001));
			int iTemp740 = (1 - iTemp739);
			int iTemp741 = (1103515245 * (iRec272[1] + 12345));
			int iTemp742 = (1103515245 * (iTemp741 + 12345));
			int iTemp743 = (1103515245 * (iTemp742 + 12345));
			int iTemp744 = (1103515245 * (iTemp743 + 12345));
			int iTemp745 = (1103515245 * (iTemp744 + 12345));
			iRec272[0] = (1103515245 * (iTemp745 + 12345));
			int iRec273 = iTemp745;
			int iRec274 = iTemp744;
			int iRec275 = iTemp743;
			int iRec276 = iTemp742;
			int iRec277 = iTemp741;
			iRec270[0] = ((iRec270[1] * iTemp740) + (iTemp739 * ((4.6566128752457969e-10 * double(iRec272[0])) > fSlow485)));
			double fTemp746 = std::pow(10.0, (0.050000000000000003 * fRec269[0]));
			double fTemp747 = (0.5 * fRec271[0]);
			double fTemp748 = (65536.0 * (fTemp747 - std::floor(fTemp747)));
			int iTemp749 = int(fTemp748);
			double fTemp750 = ftbl0FilDeSoi1PanStereoSIG0[iTemp749];
			double fTemp751 = (fTemp750 + ((fTemp748 - std::floor(fTemp748)) * (ftbl0FilDeSoi1PanStereoSIG0[((iTemp749 + 1) % 65536)] - fTemp750)));
			double fTemp752 = (((((((((((((((((fTemp736 * fRec264[0]) + (fTemp733 * fRec252[0])) + (fTemp732 * fRec246[0])) + (fTemp731 * fRec240[0])) + (fTemp730 * fRec234[0])) + (fTemp729 * fRec228[0])) + (fTemp728 * fRec222[0])) + (fTemp727 * fRec216[0])) + (fTemp726 * fRec210[0])) + (fTemp725 * fRec204[0])) + (fTemp724 * fRec198[0])) + (fTemp723 * fRec192[0])) + (fTemp722 * fRec186[0])) + (fTemp721 * fRec180[0])) + (fTemp720 * fRec174[0])) + (fTemp719 * fRec168[0])) + (((fTemp21 * fRec258[0]) * fTemp734) * fTemp735));
			fRec278[0] = (fSlow491 + (fRec278[1] - std::floor((fSlow491 + fRec278[1]))));
			double fTemp753 = (fSlow489 + (fSlow490 * std::fmod((fSlow486 + fRec278[0]), 1.0)));
			double fTemp754 = (6.2831853071795862 * fTemp753);
			double fTemp755 = (((((((((((((((((fTemp736 * fRec265[0]) + (fTemp733 * fRec253[0])) + (fTemp732 * fRec247[0])) + (fTemp731 * fRec241[0])) + (fTemp730 * fRec235[0])) + (fTemp729 * fRec229[0])) + (fTemp728 * fRec223[0])) + (fTemp727 * fRec217[0])) + (fTemp726 * fRec211[0])) + (fTemp725 * fRec205[0])) + (fTemp724 * fRec199[0])) + (fTemp723 * fRec193[0])) + (fTemp722 * fRec187[0])) + (fTemp721 * fRec181[0])) + (fTemp720 * fRec175[0])) + (fTemp719 * fRec169[0])) + (((fTemp21 * fRec259[0]) * fTemp734) * fTemp735));
			fRec279[0] = (fSlow497 + (fRec279[1] - std::floor((fSlow497 + fRec279[1]))));
			double fTemp756 = (fSlow495 + (fSlow496 * std::fmod((fSlow492 + fRec279[0]), 1.0)));
			double fTemp757 = (6.2831853071795862 * fTemp756);
			double fTemp758 = (((((((((((((((((fTemp736 * fRec267[0]) + (fTemp733 * fRec255[0])) + (fTemp732 * fRec249[0])) + (fTemp731 * fRec243[0])) + (fTemp730 * fRec237[0])) + (fTemp729 * fRec231[0])) + (fTemp728 * fRec225[0])) + (fTemp727 * fRec219[0])) + (fTemp726 * fRec213[0])) + (fTemp725 * fRec207[0])) + (fTemp724 * fRec201[0])) + (fTemp723 * fRec195[0])) + (fTemp722 * fRec189[0])) + (fTemp721 * fRec183[0])) + (fTemp720 * fRec177[0])) + (fTemp719 * fRec171[0])) + (((fTemp21 * fRec261[0]) * fTemp734) * fTemp735));
			fRec280[0] = (fSlow503 + (fRec280[1] - std::floor((fSlow503 + fRec280[1]))));
			double fTemp759 = (fSlow501 + (fSlow502 * std::fmod((fSlow498 + fRec280[0]), 1.0)));
			double fTemp760 = (6.2831853071795862 * fTemp759);
			fRec281[0] = (fSlow504 + (fConst6 * fRec281[1]));
			fRec282[0] = (fSlow505 + (fConst6 * fRec282[1]));
			fRec283[0] = (fSlow506 + (fConst6 * fRec283[1]));
			fRec284[0] = (fSlow507 + (fConst6 * fRec284[1]));
			fRec285[0] = (fSlow508 + (fConst6 * fRec285[1]));
			fRec286[0] = (fSlow509 + (fConst6 * fRec286[1]));
			fRec287[0] = (fSlow510 + (fConst6 * fRec287[1]));
			fRec288[0] = (fSlow511 + (fConst6 * fRec288[1]));
			fRec289[0] = (fSlow512 + (fConst6 * fRec289[1]));
			fRec290[0] = (fSlow513 + (fConst6 * fRec290[1]));
			fRec291[0] = (fSlow514 + (fConst6 * fRec291[1]));
			fRec292[0] = (fSlow515 + (fConst6 * fRec292[1]));
			fRec293[0] = (fSlow516 + (fConst6 * fRec293[1]));
			fRec294[0] = (fSlow517 + (fConst6 * fRec294[1]));
			fRec295[0] = (fSlow518 + (fConst6 * fRec295[1]));
			fRec296[0] = (fSlow519 + (fConst6 * fRec296[1]));
			double fTemp761 = (((((((((((((((((fTemp736 * fRec266[0]) + (fTemp733 * fRec254[0])) + (fTemp732 * fRec248[0])) + (fTemp731 * fRec242[0])) + (fTemp730 * fRec236[0])) + (fTemp729 * fRec230[0])) + (fTemp728 * fRec224[0])) + (fTemp727 * fRec218[0])) + (fTemp726 * fRec212[0])) + (fTemp725 * fRec206[0])) + (fTemp724 * fRec200[0])) + (fTemp723 * fRec194[0])) + (fTemp722 * fRec188[0])) + (fTemp721 * fRec182[0])) + (fTemp720 * fRec176[0])) + (fTemp719 * fRec170[0])) + (((fTemp21 * fRec260[0]) * fTemp734) * fTemp735));
			fRec297[0] = (fSlow525 + (fRec297[1] - std::floor((fSlow525 + fRec297[1]))));
			double fTemp762 = (fSlow523 + (fSlow524 * std::fmod((fSlow520 + fRec297[0]), 1.0)));
			double fTemp763 = (6.2831853071795862 * fTemp762);
			double fTemp764 = ((fTemp21 * (((fRec268[0] * fTemp734) * fTemp735) + (((fTemp738 * double(iRec270[0])) * fTemp746) * fTemp751))) + ((fTemp752 * std::sin(fTemp754)) + ((fTemp755 * std::sin(fTemp757)) + ((fTemp758 * std::sin(fTemp760)) + (((((((((((((((((fTemp736 * fRec281[0]) + (fTemp733 * fRec282[0])) + (fTemp732 * fRec283[0])) + (fTemp731 * fRec284[0])) + (fTemp730 * fRec285[0])) + (fTemp729 * fRec286[0])) + (fTemp728 * fRec287[0])) + (fTemp727 * fRec288[0])) + (fTemp726 * fRec289[0])) + (fTemp725 * fRec290[0])) + (fTemp724 * fRec291[0])) + (fTemp723 * fRec292[0])) + (fTemp722 * fRec293[0])) + (fTemp721 * fRec294[0])) + (fTemp720 * fRec295[0])) + (fTemp719 * fRec296[0])) + (fTemp761 * std::sin(fTemp763)))))));
			fRec298[0] = (fSlow527 + (fConst6 * fRec298[1]));
			iRec299[0] = ((iTemp740 * iRec299[1]) + (iTemp739 * ((4.6566128752457969e-10 * double(iRec273)) > fSlow485)));
			fRec300[0] = (fSlow528 + (fConst6 * fRec300[1]));
			fRec301[0] = (fSlow529 + (fConst6 * fRec301[1]));
			fRec302[0] = (fSlow530 + (fConst6 * fRec302[1]));
			fRec303[0] = (fSlow531 + (fConst6 * fRec303[1]));
			fRec304[0] = (fSlow532 + (fConst6 * fRec304[1]));
			fRec305[0] = (fSlow533 + (fConst6 * fRec305[1]));
			fRec306[0] = (fSlow534 + (fConst6 * fRec306[1]));
			fRec307[0] = (fSlow535 + (fConst6 * fRec307[1]));
			fRec308[0] = (fSlow536 + (fConst6 * fRec308[1]));
			fRec309[0] = (fSlow537 + (fConst6 * fRec309[1]));
			fRec310[0] = (fSlow538 + (fConst6 * fRec310[1]));
			fRec311[0] = (fSlow539 + (fConst6 * fRec311[1]));
			fRec312[0] = (fSlow540 + (fConst6 * fRec312[1]));
			fRec313[0] = (fSlow541 + (fConst6 * fRec313[1]));
			fRec314[0] = (fSlow542 + (fConst6 * fRec314[1]));
			fRec315[0] = (fSlow543 + (fConst6 * fRec315[1]));
			double fTemp765 = ((fTemp21 * (((fRec298[0] * fTemp734) * fTemp735) + (((fTemp738 * double(iRec299[0])) * fTemp746) * fTemp751))) + ((fTemp752 * std::cos(fTemp754)) + ((fTemp755 * std::cos(fTemp757)) + ((fTemp758 * std::cos(fTemp760)) + (((((((((((((((((fTemp736 * fRec300[0]) + (fTemp733 * fRec301[0])) + (fTemp732 * fRec302[0])) + (fTemp731 * fRec303[0])) + (fTemp730 * fRec304[0])) + (fTemp729 * fRec305[0])) + (fTemp728 * fRec306[0])) + (fTemp727 * fRec307[0])) + (fTemp726 * fRec308[0])) + (fTemp725 * fRec309[0])) + (fTemp724 * fRec310[0])) + (fTemp723 * fRec311[0])) + (fTemp722 * fRec312[0])) + (fTemp721 * fRec313[0])) + (fTemp720 * fRec314[0])) + (fTemp719 * fRec315[0])) + (fTemp761 * std::cos(fTemp763)))))));
			fRec316[0] = (fSlow546 + (fConst6 * fRec316[1]));
			iRec317[0] = ((iTemp740 * iRec317[1]) + (iTemp739 * ((4.6566128752457969e-10 * double(iRec274)) > fSlow485)));
			double fTemp766 = (12.566370614359172 * fTemp753);
			double fTemp767 = (12.566370614359172 * fTemp756);
			double fTemp768 = (12.566370614359172 * fTemp759);
			fRec318[0] = (fSlow547 + (fConst6 * fRec318[1]));
			fRec319[0] = (fSlow548 + (fConst6 * fRec319[1]));
			fRec320[0] = (fSlow549 + (fConst6 * fRec320[1]));
			fRec321[0] = (fSlow550 + (fConst6 * fRec321[1]));
			fRec322[0] = (fSlow551 + (fConst6 * fRec322[1]));
			fRec323[0] = (fSlow552 + (fConst6 * fRec323[1]));
			fRec324[0] = (fSlow553 + (fConst6 * fRec324[1]));
			fRec325[0] = (fSlow554 + (fConst6 * fRec325[1]));
			fRec326[0] = (fSlow555 + (fConst6 * fRec326[1]));
			fRec327[0] = (fSlow556 + (fConst6 * fRec327[1]));
			fRec328[0] = (fSlow557 + (fConst6 * fRec328[1]));
			fRec329[0] = (fSlow558 + (fConst6 * fRec329[1]));
			fRec330[0] = (fSlow559 + (fConst6 * fRec330[1]));
			fRec331[0] = (fSlow560 + (fConst6 * fRec331[1]));
			fRec332[0] = (fSlow561 + (fConst6 * fRec332[1]));
			fRec333[0] = (fSlow562 + (fConst6 * fRec333[1]));
			double fTemp769 = (12.566370614359172 * fTemp762);
			double fTemp770 = ((fTemp21 * (((fRec316[0] * fTemp734) * fTemp735) + (((fTemp738 * double(iRec317[0])) * fTemp746) * fTemp751))) + ((fTemp752 * std::sin(fTemp766)) + ((fTemp755 * std::sin(fTemp767)) + ((fTemp758 * std::sin(fTemp768)) + (((((((((((((((((fTemp736 * fRec318[0]) + (fTemp733 * fRec319[0])) + (fTemp732 * fRec320[0])) + (fTemp731 * fRec321[0])) + (fTemp730 * fRec322[0])) + (fTemp729 * fRec323[0])) + (fTemp728 * fRec324[0])) + (fTemp727 * fRec325[0])) + (fTemp726 * fRec326[0])) + (fTemp725 * fRec327[0])) + (fTemp724 * fRec328[0])) + (fTemp723 * fRec329[0])) + (fTemp722 * fRec330[0])) + (fTemp721 * fRec331[0])) + (fTemp720 * fRec332[0])) + (fTemp719 * fRec333[0])) + (fTemp761 * std::sin(fTemp769)))))));
			fRec334[0] = (fSlow564 + (fConst6 * fRec334[1]));
			iRec335[0] = ((iTemp740 * iRec335[1]) + (iTemp739 * ((4.6566128752457969e-10 * double(iRec275)) > fSlow485)));
			fRec336[0] = (fSlow565 + (fConst6 * fRec336[1]));
			fRec337[0] = (fSlow566 + (fConst6 * fRec337[1]));
			fRec338[0] = (fSlow567 + (fConst6 * fRec338[1]));
			fRec339[0] = (fSlow568 + (fConst6 * fRec339[1]));
			fRec340[0] = (fSlow569 + (fConst6 * fRec340[1]));
			fRec341[0] = (fSlow570 + (fConst6 * fRec341[1]));
			fRec342[0] = (fSlow571 + (fConst6 * fRec342[1]));
			fRec343[0] = (fSlow572 + (fConst6 * fRec343[1]));
			fRec344[0] = (fSlow573 + (fConst6 * fRec344[1]));
			fRec345[0] = (fSlow574 + (fConst6 * fRec345[1]));
			fRec346[0] = (fSlow575 + (fConst6 * fRec346[1]));
			fRec347[0] = (fSlow576 + (fConst6 * fRec347[1]));
			fRec348[0] = (fSlow577 + (fConst6 * fRec348[1]));
			fRec349[0] = (fSlow578 + (fConst6 * fRec349[1]));
			fRec350[0] = (fSlow579 + (fConst6 * fRec350[1]));
			fRec351[0] = (fSlow580 + (fConst6 * fRec351[1]));
			double fTemp771 = ((fTemp21 * (((fRec334[0] * fTemp734) * fTemp735) + (((fTemp738 * double(iRec335[0])) * fTemp746) * fTemp751))) + ((fTemp752 * std::cos(fTemp766)) + ((fTemp755 * std::cos(fTemp767)) + ((fTemp758 * std::cos(fTemp768)) + (((((((((((((((((fTemp736 * fRec336[0]) + (fTemp733 * fRec337[0])) + (fTemp732 * fRec338[0])) + (fTemp731 * fRec339[0])) + (fTemp730 * fRec340[0])) + (fTemp729 * fRec341[0])) + (fTemp728 * fRec342[0])) + (fTemp727 * fRec343[0])) + (fTemp726 * fRec344[0])) + (fTemp725 * fRec345[0])) + (fTemp724 * fRec346[0])) + (fTemp723 * fRec347[0])) + (fTemp722 * fRec348[0])) + (fTemp721 * fRec349[0])) + (fTemp720 * fRec350[0])) + (fTemp719 * fRec351[0])) + (fTemp761 * std::cos(fTemp769)))))));
			fRec352[0] = (fSlow583 + (fConst6 * fRec352[1]));
			iRec353[0] = ((iTemp740 * iRec353[1]) + (iTemp739 * ((4.6566128752457969e-10 * double(iRec276)) > fSlow485)));
			double fTemp772 = (18.849555921538759 * fTemp753);
			double fTemp773 = (18.849555921538759 * fTemp756);
			double fTemp774 = (18.849555921538759 * fTemp759);
			fRec354[0] = (fSlow584 + (fConst6 * fRec354[1]));
			fRec355[0] = (fSlow585 + (fConst6 * fRec355[1]));
			fRec356[0] = (fSlow586 + (fConst6 * fRec356[1]));
			fRec357[0] = (fSlow587 + (fConst6 * fRec357[1]));
			fRec358[0] = (fSlow588 + (fConst6 * fRec358[1]));
			fRec359[0] = (fSlow589 + (fConst6 * fRec359[1]));
			fRec360[0] = (fSlow590 + (fConst6 * fRec360[1]));
			fRec361[0] = (fSlow591 + (fConst6 * fRec361[1]));
			fRec362[0] = (fSlow592 + (fConst6 * fRec362[1]));
			fRec363[0] = (fSlow593 + (fConst6 * fRec363[1]));
			fRec364[0] = (fSlow594 + (fConst6 * fRec364[1]));
			fRec365[0] = (fSlow595 + (fConst6 * fRec365[1]));
			fRec366[0] = (fSlow596 + (fConst6 * fRec366[1]));
			fRec367[0] = (fSlow597 + (fConst6 * fRec367[1]));
			fRec368[0] = (fSlow598 + (fConst6 * fRec368[1]));
			fRec369[0] = (fSlow599 + (fConst6 * fRec369[1]));
			double fTemp775 = (18.849555921538759 * fTemp762);
			double fTemp776 = ((fTemp21 * (((fRec352[0] * fTemp734) * fTemp735) + (((fTemp738 * double(iRec353[0])) * fTemp746) * fTemp751))) + ((fTemp752 * std::sin(fTemp772)) + ((fTemp755 * std::sin(fTemp773)) + ((fTemp758 * std::sin(fTemp774)) + (((((((((((((((((fTemp736 * fRec354[0]) + (fTemp733 * fRec355[0])) + (fTemp732 * fRec356[0])) + (fTemp731 * fRec357[0])) + (fTemp730 * fRec358[0])) + (fTemp729 * fRec359[0])) + (fTemp728 * fRec360[0])) + (fTemp727 * fRec361[0])) + (fTemp726 * fRec362[0])) + (fTemp725 * fRec363[0])) + (fTemp724 * fRec364[0])) + (fTemp723 * fRec365[0])) + (fTemp722 * fRec366[0])) + (fTemp721 * fRec367[0])) + (fTemp720 * fRec368[0])) + (fTemp719 * fRec369[0])) + (fTemp761 * std::sin(fTemp775)))))));
			fRec370[0] = (fSlow601 + (fConst6 * fRec370[1]));
			iRec371[0] = ((iTemp740 * iRec371[1]) + (iTemp739 * ((4.6566128752457969e-10 * double(iRec277)) > fSlow485)));
			fRec372[0] = (fSlow602 + (fConst6 * fRec372[1]));
			fRec373[0] = (fSlow603 + (fConst6 * fRec373[1]));
			fRec374[0] = (fSlow604 + (fConst6 * fRec374[1]));
			fRec375[0] = (fSlow605 + (fConst6 * fRec375[1]));
			fRec376[0] = (fSlow606 + (fConst6 * fRec376[1]));
			fRec377[0] = (fSlow607 + (fConst6 * fRec377[1]));
			fRec378[0] = (fSlow608 + (fConst6 * fRec378[1]));
			fRec379[0] = (fSlow609 + (fConst6 * fRec379[1]));
			fRec380[0] = (fSlow610 + (fConst6 * fRec380[1]));
			fRec381[0] = (fSlow611 + (fConst6 * fRec381[1]));
			fRec382[0] = (fSlow612 + (fConst6 * fRec382[1]));
			fRec383[0] = (fSlow613 + (fConst6 * fRec383[1]));
			fRec384[0] = (fSlow614 + (fConst6 * fRec384[1]));
			fRec385[0] = (fSlow615 + (fConst6 * fRec385[1]));
			fRec386[0] = (fSlow616 + (fConst6 * fRec386[1]));
			fRec387[0] = (fSlow617 + (fConst6 * fRec387[1]));
			double fTemp777 = ((fTemp21 * (((fRec370[0] * fTemp734) * fTemp735) + (((double(iRec371[0]) * fTemp738) * fTemp746) * fTemp751))) + ((fTemp752 * std::cos(fTemp772)) + ((fTemp755 * std::cos(fTemp773)) + ((fTemp758 * std::cos(fTemp774)) + (((((((((((((((((fTemp736 * fRec372[0]) + (fTemp733 * fRec373[0])) + (fTemp732 * fRec374[0])) + (fTemp731 * fRec375[0])) + (fTemp730 * fRec376[0])) + (fTemp729 * fRec377[0])) + (fTemp728 * fRec378[0])) + (fTemp727 * fRec379[0])) + (fTemp726 * fRec380[0])) + (fTemp725 * fRec381[0])) + (fTemp724 * fRec382[0])) + (fTemp723 * fRec383[0])) + (fTemp722 * fRec384[0])) + (fTemp721 * fRec385[0])) + (fTemp720 * fRec386[0])) + (fTemp719 * fRec387[0])) + (fTemp761 * std::cos(fTemp775)))))));
			double fTemp778 = ((((((fTemp737 + (fSlow481 * fTemp764)) + (fSlow526 * fTemp765)) + (fSlow545 * fTemp770)) + (fSlow563 * fTemp771)) + (fSlow582 * fTemp776)) + (fSlow600 * fTemp777));
			fRec388[0] = (fSlow618 + (0.999 * fRec388[1]));
			double fTemp779 = (-1.0 * fRec388[0]);
			double fTemp780 = std::max<double>(std::min<double>(fRec388[0], (0.0 - fRec388[0])), fTemp779);
			double fTemp781 = ((((((fTemp737 + (fSlow621 * fTemp764)) + (fSlow622 * fTemp765)) + (fSlow624 * fTemp770)) + (fSlow625 * fTemp771)) + (fSlow627 * fTemp776)) + (fSlow628 * fTemp777));
			double fTemp782 = std::max<double>(std::min<double>(fRec388[0], (0.0 - (0.7142857142857143 * fRec388[0]))), fTemp779);
			double fTemp783 = ((((((fTemp737 + (fSlow631 * fTemp764)) + (fSlow632 * fTemp765)) + (fSlow634 * fTemp770)) + (fSlow635 * fTemp771)) + (fSlow637 * fTemp776)) + (fSlow638 * fTemp777));
			double fTemp784 = (0.4285714285714286 * fRec388[0]);
			double fTemp785 = std::max<double>(std::min<double>(fRec388[0], (0.0 - fTemp784)), fTemp779);
			double fTemp786 = ((((((fTemp737 + (fSlow641 * fTemp764)) + (fSlow642 * fTemp765)) + (fSlow644 * fTemp770)) + (fSlow645 * fTemp771)) + (fSlow647 * fTemp776)) + (fSlow648 * fTemp777));
			double fTemp787 = std::max<double>(std::min<double>(fRec388[0], (0.0 - (0.1428571428571429 * fRec388[0]))), fTemp779);
			double fTemp788 = ((((((fTemp737 + (fSlow651 * fTemp764)) + (fSlow652 * fTemp765)) + (fSlow654 * fTemp770)) + (fSlow655 * fTemp771)) + (fSlow657 * fTemp776)) + (fSlow658 * fTemp777));
			double fTemp789 = std::max<double>(std::min<double>(fRec388[0], (0.14285714285714279 * fRec388[0])), fTemp779);
			double fTemp790 = ((((((fTemp737 + (fSlow661 * fTemp764)) + (fSlow662 * fTemp765)) + (fSlow664 * fTemp770)) + (fSlow665 * fTemp771)) + (fSlow667 * fTemp776)) + (fSlow668 * fTemp777));
			double fTemp791 = std::max<double>(std::min<double>(fRec388[0], fTemp784), fTemp779);
			double fTemp792 = ((((((fTemp737 + (fSlow671 * fTemp764)) + (fSlow672 * fTemp765)) + (fSlow674 * fTemp770)) + (fSlow675 * fTemp771)) + (fSlow677 * fTemp776)) + (fSlow678 * fTemp777));
			double fTemp793 = std::max<double>(std::min<double>(fRec388[0], (0.71428571428571419 * fRec388[0])), fTemp779);
			double fTemp794 = ((((((fTemp737 + (fSlow681 * fTemp764)) + (fSlow682 * fTemp765)) + (fSlow684 * fTemp770)) + (fSlow685 * fTemp771)) + (fSlow687 * fTemp776)) + (fSlow688 * fTemp777));
			double fTemp795 = std::max<double>(std::min<double>(fRec388[0], fRec388[0]), fTemp779);
			output0[i] = FAUSTFLOAT((fTemp0 * ((((((((fTemp778 * std::sqrt((0.5 * ((fRec388[0] - fTemp780) / fRec388[0])))) + (fTemp781 * std::sqrt((0.5 * ((fRec388[0] - fTemp782) / fRec388[0]))))) + (fTemp783 * std::sqrt((0.5 * ((fRec388[0] - fTemp785) / fRec388[0]))))) + (fTemp786 * std::sqrt((0.5 * ((fRec388[0] - fTemp787) / fRec388[0]))))) + (fTemp788 * std::sqrt((0.5 * ((fRec388[0] - fTemp789) / fRec388[0]))))) + (fTemp790 * std::sqrt((0.5 * ((fRec388[0] - fTemp791) / fRec388[0]))))) + (fTemp792 * std::sqrt((0.5 * ((fRec388[0] - fTemp793) / fRec388[0]))))) + (fTemp794 * std::sqrt((0.5 * ((fRec388[0] - fTemp795) / fRec388[0])))))));
			output1[i] = FAUSTFLOAT((fTemp0 * ((((((((fTemp778 * std::sqrt((0.5 * ((fRec388[0] + fTemp780) / fRec388[0])))) + (fTemp781 * std::sqrt((0.5 * ((fRec388[0] + fTemp782) / fRec388[0]))))) + (fTemp783 * std::sqrt((0.5 * ((fRec388[0] + fTemp785) / fRec388[0]))))) + (fTemp786 * std::sqrt((0.5 * ((fRec388[0] + fTemp787) / fRec388[0]))))) + (fTemp788 * std::sqrt((0.5 * ((fRec388[0] + fTemp789) / fRec388[0]))))) + (fTemp790 * std::sqrt((0.5 * ((fRec388[0] + fTemp791) / fRec388[0]))))) + (fTemp792 * std::sqrt((0.5 * ((fRec388[0] + fTemp793) / fRec388[0]))))) + (fTemp794 * std::sqrt((0.5 * ((fRec388[0] + fTemp795) / fRec388[0])))))));
			fRec0[1] = fRec0[0];
			fRec18[1] = fRec18[0];
			fVec0[1] = fVec0[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			IOTA = (IOTA + 1);
			iRec37[1] = iRec37[0];
			fVec2[1] = fVec2[0];
			iRec38[1] = iRec38[0];
			fVec4[1] = fVec4[0];
			fRec41[1] = fRec41[0];
			fRec42[1] = fRec42[0];
			fRec40[1] = fRec40[0];
			fVec5[1] = fVec5[0];
			fRec39[1] = fRec39[0];
			fVec6[1] = fVec6[0];
			fRec43[1] = fRec43[0];
			fVec7[1] = fVec7[0];
			fRec44[1] = fRec44[0];
			fVec8[1] = fVec8[0];
			fRec45[1] = fRec45[0];
			fRec1[1] = fRec1[0];
			fRec46[1] = fRec46[0];
			iRec47[1] = iRec47[0];
			iRec48[1] = iRec48[0];
			fRec50[1] = fRec50[0];
			fVec11[1] = fVec11[0];
			fRec49[1] = fRec49[0];
			fVec12[1] = fVec12[0];
			fRec51[1] = fRec51[0];
			fVec13[1] = fVec13[0];
			fRec52[1] = fRec52[0];
			fVec14[1] = fVec14[0];
			fRec53[1] = fRec53[0];
			fRec2[1] = fRec2[0];
			fRec54[1] = fRec54[0];
			iRec55[1] = iRec55[0];
			iRec56[1] = iRec56[0];
			fRec58[1] = fRec58[0];
			fVec17[1] = fVec17[0];
			fRec57[1] = fRec57[0];
			fVec18[1] = fVec18[0];
			fRec59[1] = fRec59[0];
			fVec19[1] = fVec19[0];
			fRec60[1] = fRec60[0];
			fVec20[1] = fVec20[0];
			fRec61[1] = fRec61[0];
			fRec3[1] = fRec3[0];
			fRec62[1] = fRec62[0];
			iRec63[1] = iRec63[0];
			iRec64[1] = iRec64[0];
			fRec66[1] = fRec66[0];
			fVec23[1] = fVec23[0];
			fRec65[1] = fRec65[0];
			fVec24[1] = fVec24[0];
			fRec67[1] = fRec67[0];
			fVec25[1] = fVec25[0];
			fRec68[1] = fRec68[0];
			fVec26[1] = fVec26[0];
			fRec69[1] = fRec69[0];
			fRec4[1] = fRec4[0];
			fRec70[1] = fRec70[0];
			iRec71[1] = iRec71[0];
			iRec72[1] = iRec72[0];
			fRec74[1] = fRec74[0];
			fVec29[1] = fVec29[0];
			fRec73[1] = fRec73[0];
			fVec30[1] = fVec30[0];
			fRec75[1] = fRec75[0];
			fVec31[1] = fVec31[0];
			fRec76[1] = fRec76[0];
			fVec32[1] = fVec32[0];
			fRec77[1] = fRec77[0];
			fRec5[1] = fRec5[0];
			fRec78[1] = fRec78[0];
			iRec79[1] = iRec79[0];
			iRec80[1] = iRec80[0];
			fRec82[1] = fRec82[0];
			fVec35[1] = fVec35[0];
			fRec81[1] = fRec81[0];
			fVec36[1] = fVec36[0];
			fRec83[1] = fRec83[0];
			fVec37[1] = fVec37[0];
			fRec84[1] = fRec84[0];
			fVec38[1] = fVec38[0];
			fRec85[1] = fRec85[0];
			fRec6[1] = fRec6[0];
			fRec86[1] = fRec86[0];
			iRec87[1] = iRec87[0];
			iRec88[1] = iRec88[0];
			fRec90[1] = fRec90[0];
			fVec41[1] = fVec41[0];
			fRec89[1] = fRec89[0];
			fVec42[1] = fVec42[0];
			fRec91[1] = fRec91[0];
			fVec43[1] = fVec43[0];
			fRec92[1] = fRec92[0];
			fVec44[1] = fVec44[0];
			fRec93[1] = fRec93[0];
			fRec7[1] = fRec7[0];
			fRec94[1] = fRec94[0];
			iRec95[1] = iRec95[0];
			iRec96[1] = iRec96[0];
			fRec98[1] = fRec98[0];
			fVec47[1] = fVec47[0];
			fRec97[1] = fRec97[0];
			fVec48[1] = fVec48[0];
			fRec99[1] = fRec99[0];
			fVec49[1] = fVec49[0];
			fRec100[1] = fRec100[0];
			fVec50[1] = fVec50[0];
			fRec101[1] = fRec101[0];
			fRec8[1] = fRec8[0];
			fRec102[1] = fRec102[0];
			iRec103[1] = iRec103[0];
			iRec104[1] = iRec104[0];
			fRec106[1] = fRec106[0];
			fVec53[1] = fVec53[0];
			fRec105[1] = fRec105[0];
			fVec54[1] = fVec54[0];
			fRec107[1] = fRec107[0];
			fVec55[1] = fVec55[0];
			fRec108[1] = fRec108[0];
			fVec56[1] = fVec56[0];
			fRec109[1] = fRec109[0];
			fRec9[1] = fRec9[0];
			fRec110[1] = fRec110[0];
			iRec111[1] = iRec111[0];
			iRec112[1] = iRec112[0];
			fRec114[1] = fRec114[0];
			fVec59[1] = fVec59[0];
			fRec113[1] = fRec113[0];
			fVec60[1] = fVec60[0];
			fRec115[1] = fRec115[0];
			fVec61[1] = fVec61[0];
			fRec116[1] = fRec116[0];
			fVec62[1] = fVec62[0];
			fRec117[1] = fRec117[0];
			fRec10[1] = fRec10[0];
			fRec118[1] = fRec118[0];
			iRec119[1] = iRec119[0];
			iRec120[1] = iRec120[0];
			fRec122[1] = fRec122[0];
			fVec65[1] = fVec65[0];
			fRec121[1] = fRec121[0];
			fVec66[1] = fVec66[0];
			fRec123[1] = fRec123[0];
			fVec67[1] = fVec67[0];
			fRec124[1] = fRec124[0];
			fVec68[1] = fVec68[0];
			fRec125[1] = fRec125[0];
			fRec11[1] = fRec11[0];
			fRec126[1] = fRec126[0];
			iRec127[1] = iRec127[0];
			iRec128[1] = iRec128[0];
			fRec130[1] = fRec130[0];
			fVec71[1] = fVec71[0];
			fRec129[1] = fRec129[0];
			fVec72[1] = fVec72[0];
			fRec131[1] = fRec131[0];
			fVec73[1] = fVec73[0];
			fRec132[1] = fRec132[0];
			fVec74[1] = fVec74[0];
			fRec133[1] = fRec133[0];
			fRec12[1] = fRec12[0];
			fRec134[1] = fRec134[0];
			iRec135[1] = iRec135[0];
			iRec136[1] = iRec136[0];
			fRec138[1] = fRec138[0];
			fVec77[1] = fVec77[0];
			fRec137[1] = fRec137[0];
			fVec78[1] = fVec78[0];
			fRec139[1] = fRec139[0];
			fVec79[1] = fVec79[0];
			fRec140[1] = fRec140[0];
			fVec80[1] = fVec80[0];
			fRec141[1] = fRec141[0];
			fRec13[1] = fRec13[0];
			fRec142[1] = fRec142[0];
			iRec143[1] = iRec143[0];
			iRec144[1] = iRec144[0];
			fRec146[1] = fRec146[0];
			fVec83[1] = fVec83[0];
			fRec145[1] = fRec145[0];
			fVec84[1] = fVec84[0];
			fRec147[1] = fRec147[0];
			fVec85[1] = fVec85[0];
			fRec148[1] = fRec148[0];
			fVec86[1] = fVec86[0];
			fRec149[1] = fRec149[0];
			fRec14[1] = fRec14[0];
			fRec150[1] = fRec150[0];
			iRec151[1] = iRec151[0];
			iRec152[1] = iRec152[0];
			fRec154[1] = fRec154[0];
			fVec89[1] = fVec89[0];
			fRec153[1] = fRec153[0];
			fVec90[1] = fVec90[0];
			fRec155[1] = fRec155[0];
			fVec91[1] = fVec91[0];
			fRec156[1] = fRec156[0];
			fVec92[1] = fVec92[0];
			fRec157[1] = fRec157[0];
			fRec15[1] = fRec15[0];
			fRec158[1] = fRec158[0];
			iRec159[1] = iRec159[0];
			iRec160[1] = iRec160[0];
			fRec162[1] = fRec162[0];
			fVec95[1] = fVec95[0];
			fRec161[1] = fRec161[0];
			fVec96[1] = fVec96[0];
			fRec163[1] = fRec163[0];
			fVec97[1] = fVec97[0];
			fRec164[1] = fRec164[0];
			fVec98[1] = fVec98[0];
			fRec165[1] = fRec165[0];
			fRec16[1] = fRec16[0];
			fRec166[1] = fRec166[0];
			fRec167[1] = fRec167[0];
			fRec168[1] = fRec168[0];
			fRec169[1] = fRec169[0];
			fRec170[1] = fRec170[0];
			fRec171[1] = fRec171[0];
			fRec172[1] = fRec172[0];
			fRec173[1] = fRec173[0];
			fRec174[1] = fRec174[0];
			fRec175[1] = fRec175[0];
			fRec176[1] = fRec176[0];
			fRec177[1] = fRec177[0];
			fRec178[1] = fRec178[0];
			fRec179[1] = fRec179[0];
			fRec180[1] = fRec180[0];
			fRec181[1] = fRec181[0];
			fRec182[1] = fRec182[0];
			fRec183[1] = fRec183[0];
			fRec184[1] = fRec184[0];
			fRec185[1] = fRec185[0];
			fRec186[1] = fRec186[0];
			fRec187[1] = fRec187[0];
			fRec188[1] = fRec188[0];
			fRec189[1] = fRec189[0];
			fRec190[1] = fRec190[0];
			fRec191[1] = fRec191[0];
			fRec192[1] = fRec192[0];
			fRec193[1] = fRec193[0];
			fRec194[1] = fRec194[0];
			fRec195[1] = fRec195[0];
			fRec196[1] = fRec196[0];
			fRec197[1] = fRec197[0];
			fRec198[1] = fRec198[0];
			fRec199[1] = fRec199[0];
			fRec200[1] = fRec200[0];
			fRec201[1] = fRec201[0];
			fRec202[1] = fRec202[0];
			fRec203[1] = fRec203[0];
			fRec204[1] = fRec204[0];
			fRec205[1] = fRec205[0];
			fRec206[1] = fRec206[0];
			fRec207[1] = fRec207[0];
			fRec208[1] = fRec208[0];
			fRec209[1] = fRec209[0];
			fRec210[1] = fRec210[0];
			fRec211[1] = fRec211[0];
			fRec212[1] = fRec212[0];
			fRec213[1] = fRec213[0];
			fRec214[1] = fRec214[0];
			fRec215[1] = fRec215[0];
			fRec216[1] = fRec216[0];
			fRec217[1] = fRec217[0];
			fRec218[1] = fRec218[0];
			fRec219[1] = fRec219[0];
			fRec220[1] = fRec220[0];
			fRec221[1] = fRec221[0];
			fRec222[1] = fRec222[0];
			fRec223[1] = fRec223[0];
			fRec224[1] = fRec224[0];
			fRec225[1] = fRec225[0];
			fRec226[1] = fRec226[0];
			fRec227[1] = fRec227[0];
			fRec228[1] = fRec228[0];
			fRec229[1] = fRec229[0];
			fRec230[1] = fRec230[0];
			fRec231[1] = fRec231[0];
			fRec232[1] = fRec232[0];
			fRec233[1] = fRec233[0];
			fRec234[1] = fRec234[0];
			fRec235[1] = fRec235[0];
			fRec236[1] = fRec236[0];
			fRec237[1] = fRec237[0];
			fRec238[1] = fRec238[0];
			fRec239[1] = fRec239[0];
			fRec240[1] = fRec240[0];
			fRec241[1] = fRec241[0];
			fRec242[1] = fRec242[0];
			fRec243[1] = fRec243[0];
			fRec244[1] = fRec244[0];
			fRec245[1] = fRec245[0];
			fRec246[1] = fRec246[0];
			fRec247[1] = fRec247[0];
			fRec248[1] = fRec248[0];
			fRec249[1] = fRec249[0];
			fRec250[1] = fRec250[0];
			fRec251[1] = fRec251[0];
			fRec252[1] = fRec252[0];
			fRec253[1] = fRec253[0];
			fRec254[1] = fRec254[0];
			fRec255[1] = fRec255[0];
			fRec256[1] = fRec256[0];
			fRec257[1] = fRec257[0];
			fRec258[1] = fRec258[0];
			fRec259[1] = fRec259[0];
			fRec260[1] = fRec260[0];
			fRec261[1] = fRec261[0];
			fRec262[1] = fRec262[0];
			fRec263[1] = fRec263[0];
			fRec264[1] = fRec264[0];
			fRec265[1] = fRec265[0];
			fRec266[1] = fRec266[0];
			fRec267[1] = fRec267[0];
			fRec268[1] = fRec268[0];
			fRec269[1] = fRec269[0];
			fRec271[1] = fRec271[0];
			iRec272[1] = iRec272[0];
			iRec270[1] = iRec270[0];
			fRec278[1] = fRec278[0];
			fRec279[1] = fRec279[0];
			fRec280[1] = fRec280[0];
			fRec281[1] = fRec281[0];
			fRec282[1] = fRec282[0];
			fRec283[1] = fRec283[0];
			fRec284[1] = fRec284[0];
			fRec285[1] = fRec285[0];
			fRec286[1] = fRec286[0];
			fRec287[1] = fRec287[0];
			fRec288[1] = fRec288[0];
			fRec289[1] = fRec289[0];
			fRec290[1] = fRec290[0];
			fRec291[1] = fRec291[0];
			fRec292[1] = fRec292[0];
			fRec293[1] = fRec293[0];
			fRec294[1] = fRec294[0];
			fRec295[1] = fRec295[0];
			fRec296[1] = fRec296[0];
			fRec297[1] = fRec297[0];
			fRec298[1] = fRec298[0];
			iRec299[1] = iRec299[0];
			fRec300[1] = fRec300[0];
			fRec301[1] = fRec301[0];
			fRec302[1] = fRec302[0];
			fRec303[1] = fRec303[0];
			fRec304[1] = fRec304[0];
			fRec305[1] = fRec305[0];
			fRec306[1] = fRec306[0];
			fRec307[1] = fRec307[0];
			fRec308[1] = fRec308[0];
			fRec309[1] = fRec309[0];
			fRec310[1] = fRec310[0];
			fRec311[1] = fRec311[0];
			fRec312[1] = fRec312[0];
			fRec313[1] = fRec313[0];
			fRec314[1] = fRec314[0];
			fRec315[1] = fRec315[0];
			fRec316[1] = fRec316[0];
			iRec317[1] = iRec317[0];
			fRec318[1] = fRec318[0];
			fRec319[1] = fRec319[0];
			fRec320[1] = fRec320[0];
			fRec321[1] = fRec321[0];
			fRec322[1] = fRec322[0];
			fRec323[1] = fRec323[0];
			fRec324[1] = fRec324[0];
			fRec325[1] = fRec325[0];
			fRec326[1] = fRec326[0];
			fRec327[1] = fRec327[0];
			fRec328[1] = fRec328[0];
			fRec329[1] = fRec329[0];
			fRec330[1] = fRec330[0];
			fRec331[1] = fRec331[0];
			fRec332[1] = fRec332[0];
			fRec333[1] = fRec333[0];
			fRec334[1] = fRec334[0];
			iRec335[1] = iRec335[0];
			fRec336[1] = fRec336[0];
			fRec337[1] = fRec337[0];
			fRec338[1] = fRec338[0];
			fRec339[1] = fRec339[0];
			fRec340[1] = fRec340[0];
			fRec341[1] = fRec341[0];
			fRec342[1] = fRec342[0];
			fRec343[1] = fRec343[0];
			fRec344[1] = fRec344[0];
			fRec345[1] = fRec345[0];
			fRec346[1] = fRec346[0];
			fRec347[1] = fRec347[0];
			fRec348[1] = fRec348[0];
			fRec349[1] = fRec349[0];
			fRec350[1] = fRec350[0];
			fRec351[1] = fRec351[0];
			fRec352[1] = fRec352[0];
			iRec353[1] = iRec353[0];
			fRec354[1] = fRec354[0];
			fRec355[1] = fRec355[0];
			fRec356[1] = fRec356[0];
			fRec357[1] = fRec357[0];
			fRec358[1] = fRec358[0];
			fRec359[1] = fRec359[0];
			fRec360[1] = fRec360[0];
			fRec361[1] = fRec361[0];
			fRec362[1] = fRec362[0];
			fRec363[1] = fRec363[0];
			fRec364[1] = fRec364[0];
			fRec365[1] = fRec365[0];
			fRec366[1] = fRec366[0];
			fRec367[1] = fRec367[0];
			fRec368[1] = fRec368[0];
			fRec369[1] = fRec369[0];
			fRec370[1] = fRec370[0];
			iRec371[1] = iRec371[0];
			fRec372[1] = fRec372[0];
			fRec373[1] = fRec373[0];
			fRec374[1] = fRec374[0];
			fRec375[1] = fRec375[0];
			fRec376[1] = fRec376[0];
			fRec377[1] = fRec377[0];
			fRec378[1] = fRec378[0];
			fRec379[1] = fRec379[0];
			fRec380[1] = fRec380[0];
			fRec381[1] = fRec381[0];
			fRec382[1] = fRec382[0];
			fRec383[1] = fRec383[0];
			fRec384[1] = fRec384[0];
			fRec385[1] = fRec385[0];
			fRec386[1] = fRec386[0];
			fRec387[1] = fRec387[0];
			fRec388[1] = fRec388[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "FilDeSoi1PanStereo.dsp"
	#define FAUST_CLASS_NAME "FilDeSoi1PanStereo"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 566
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Encoders/rotfreq0", fHslider113, 0.10000000000000001, -10.0, 10.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotfreq1", fHslider111, 0.10000000000000001, -10.0, 10.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotfreq2", fHslider109, 0.10000000000000001, -10.0, 10.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotfreq3", fHslider107, 0.10000000000000001, -10.0, 10.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotphase0", fHslider112, 0.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotphase1", fHslider110, 0.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotphase2", fHslider108, 0.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Encoders/rotphase3", fHslider106, 0.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/dStretch", fHslider36, 1.0, 0.01, 10.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/delharmoGain", fHslider35, 0.0, -127.0, 18.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/generalGain", fHslider0, 0.0, -127.0, 18.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/guitarGain", fHslider101, -34.0, -127.0, 18.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/hStretch", fHslider38, 1.0, -10.0, 10.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/hWin", fHslider40, 64.0, 1.0, 127.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Global_Parameters/smoothDuration", fHslider1, 20.0, 10.0, 5000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 0", fHslider37, 100.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 1", fHslider42, 200.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 2", fHslider45, 300.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 3", fHslider48, 400.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 4", fHslider51, 500.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 5", fHslider54, 600.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 6", fHslider57, 700.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 7", fHslider60, 800.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 8", fHslider63, 900.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d 9", fHslider66, 1000.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d10", fHslider69, 1100.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d11", fHslider72, 1200.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d12", fHslider75, 1300.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d13", fHslider78, 1400.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d14", fHslider81, 1500.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Durations/d15", fHslider84, 1600.0, 0.0, 21000.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 0", fHslider3, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 1", fHslider5, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 2", fHslider7, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 3", fHslider9, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 4", fHslider11, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 5", fHslider13, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 6", fHslider15, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 7", fHslider17, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 8", fHslider19, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd 9", fHslider21, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd10", fHslider23, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd11", fHslider25, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd12", fHslider27, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd13", fHslider29, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd14", fHslider31, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Del_Feedbacks/fd15", fHslider33, 0.0, 0.0, 0.98999999999999999, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 0", fHslider2, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 1", fHslider4, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 2", fHslider6, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 3", fHslider8, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 4", fHslider10, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 5", fHslider12, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 6", fHslider14, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 7", fHslider16, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 8", fHslider18, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd 9", fHslider20, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd10", fHslider22, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd11", fHslider24, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd12", fHslider26, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd13", fHslider28, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd14", fHslider30, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/EffeX_vs_Del/xvd15", fHslider32, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 0", fHslider39, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 1", fHslider43, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 2", fHslider46, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 3", fHslider49, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 4", fHslider52, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 5", fHslider55, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 6", fHslider58, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 7", fHslider61, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 8", fHslider64, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr 9", fHslider67, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr10", fHslider70, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr11", fHslider73, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr12", fHslider76, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr13", fHslider79, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr14", fHslider82, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Harmo_Transpositions/tr15", fHslider85, 0.0, -2400.0, 2400.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 0", fHslider34, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 1", fHslider41, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 2", fHslider44, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 3", fHslider47, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 4", fHslider50, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 5", fHslider53, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 6", fHslider56, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 7", fHslider59, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 8", fHslider62, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp 9", fHslider65, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp10", fHslider68, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp11", fHslider71, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp12", fHslider74, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp13", fHslider77, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp14", fHslider80, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_input/inp15", fHslider83, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 0", fHslider102, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 1", fHslider100, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 2", fHslider99, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 3", fHslider98, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 4", fHslider97, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 5", fHslider96, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 6", fHslider95, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 7", fHslider94, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 8", fHslider93, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out 9", fHslider92, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out10", fHslider91, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out11", fHslider90, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out12", fHslider89, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out13", fHslider88, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out14", fHslider87, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("Lines/Line_output/out15", fHslider86, 1.0, 0.0, 1.0, 0.01);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r  0", fCheckbox0);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r 16", fCheckbox16);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r 32", fCheckbox32);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r 48", fCheckbox48);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r 64", fCheckbox64);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r 80", fCheckbox80);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r 96", fCheckbox96);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r112", fCheckbox112);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r128", fCheckbox128);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r144", fCheckbox144);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r160", fCheckbox160);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r176", fCheckbox176);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r192", fCheckbox192);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r208", fCheckbox208);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r224", fCheckbox224);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 0-->/r240", fCheckbox240);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r  1", fCheckbox1);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r 17", fCheckbox17);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r 33", fCheckbox33);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r 49", fCheckbox49);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r 65", fCheckbox65);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r 81", fCheckbox81);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r 97", fCheckbox97);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r113", fCheckbox113);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r129", fCheckbox129);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r145", fCheckbox145);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r161", fCheckbox161);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r177", fCheckbox177);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r193", fCheckbox193);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r209", fCheckbox209);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r225", fCheckbox225);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 1-->/r241", fCheckbox241);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r  2", fCheckbox2);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r 18", fCheckbox18);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r 34", fCheckbox34);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r 50", fCheckbox50);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r 66", fCheckbox66);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r 82", fCheckbox82);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r 98", fCheckbox98);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r114", fCheckbox114);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r130", fCheckbox130);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r146", fCheckbox146);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r162", fCheckbox162);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r178", fCheckbox178);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r194", fCheckbox194);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r210", fCheckbox210);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r226", fCheckbox226);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 2-->/r242", fCheckbox242);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r  3", fCheckbox3);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r 19", fCheckbox19);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r 35", fCheckbox35);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r 51", fCheckbox51);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r 67", fCheckbox67);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r 83", fCheckbox83);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r 99", fCheckbox99);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r115", fCheckbox115);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r131", fCheckbox131);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r147", fCheckbox147);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r163", fCheckbox163);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r179", fCheckbox179);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r195", fCheckbox195);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r211", fCheckbox211);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r227", fCheckbox227);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 3-->/r243", fCheckbox243);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r  4", fCheckbox4);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r 20", fCheckbox20);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r 36", fCheckbox36);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r 52", fCheckbox52);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r 68", fCheckbox68);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r 84", fCheckbox84);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r100", fCheckbox100);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r116", fCheckbox116);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r132", fCheckbox132);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r148", fCheckbox148);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r164", fCheckbox164);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r180", fCheckbox180);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r196", fCheckbox196);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r212", fCheckbox212);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r228", fCheckbox228);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 4-->/r244", fCheckbox244);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r  5", fCheckbox5);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r 21", fCheckbox21);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r 37", fCheckbox37);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r 53", fCheckbox53);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r 69", fCheckbox69);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r 85", fCheckbox85);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r101", fCheckbox101);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r117", fCheckbox117);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r133", fCheckbox133);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r149", fCheckbox149);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r165", fCheckbox165);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r181", fCheckbox181);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r197", fCheckbox197);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r213", fCheckbox213);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r229", fCheckbox229);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 5-->/r245", fCheckbox245);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r  6", fCheckbox6);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r 22", fCheckbox22);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r 38", fCheckbox38);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r 54", fCheckbox54);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r 70", fCheckbox70);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r 86", fCheckbox86);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r102", fCheckbox102);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r118", fCheckbox118);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r134", fCheckbox134);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r150", fCheckbox150);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r166", fCheckbox166);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r182", fCheckbox182);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r198", fCheckbox198);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r214", fCheckbox214);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r230", fCheckbox230);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 6-->/r246", fCheckbox246);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r  7", fCheckbox7);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r 23", fCheckbox23);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r 39", fCheckbox39);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r 55", fCheckbox55);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r 71", fCheckbox71);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r 87", fCheckbox87);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r103", fCheckbox103);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r119", fCheckbox119);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r135", fCheckbox135);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r151", fCheckbox151);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r167", fCheckbox167);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r183", fCheckbox183);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r199", fCheckbox199);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r215", fCheckbox215);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r231", fCheckbox231);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 7-->/r247", fCheckbox247);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r  8", fCheckbox8);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r 24", fCheckbox24);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r 40", fCheckbox40);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r 56", fCheckbox56);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r 72", fCheckbox72);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r 88", fCheckbox88);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r104", fCheckbox104);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r120", fCheckbox120);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r136", fCheckbox136);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r152", fCheckbox152);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r168", fCheckbox168);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r184", fCheckbox184);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r200", fCheckbox200);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r216", fCheckbox216);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r232", fCheckbox232);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 8-->/r248", fCheckbox248);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r  9", fCheckbox9);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r 25", fCheckbox25);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r 41", fCheckbox41);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r 57", fCheckbox57);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r 73", fCheckbox73);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r 89", fCheckbox89);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r105", fCheckbox105);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r121", fCheckbox121);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r137", fCheckbox137);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r153", fCheckbox153);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r169", fCheckbox169);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r185", fCheckbox185);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r201", fCheckbox201);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r217", fCheckbox217);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r233", fCheckbox233);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del 9-->/r249", fCheckbox249);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r 10", fCheckbox10);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r 26", fCheckbox26);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r 42", fCheckbox42);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r 58", fCheckbox58);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r 74", fCheckbox74);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r 90", fCheckbox90);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r106", fCheckbox106);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r122", fCheckbox122);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r138", fCheckbox138);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r154", fCheckbox154);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r170", fCheckbox170);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r186", fCheckbox186);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r202", fCheckbox202);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r218", fCheckbox218);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r234", fCheckbox234);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del10-->/r250", fCheckbox250);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r 11", fCheckbox11);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r 27", fCheckbox27);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r 43", fCheckbox43);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r 59", fCheckbox59);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r 75", fCheckbox75);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r 91", fCheckbox91);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r107", fCheckbox107);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r123", fCheckbox123);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r139", fCheckbox139);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r155", fCheckbox155);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r171", fCheckbox171);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r187", fCheckbox187);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r203", fCheckbox203);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r219", fCheckbox219);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r235", fCheckbox235);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del11-->/r251", fCheckbox251);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r 12", fCheckbox12);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r 28", fCheckbox28);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r 44", fCheckbox44);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r 60", fCheckbox60);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r 76", fCheckbox76);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r 92", fCheckbox92);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r108", fCheckbox108);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r124", fCheckbox124);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r140", fCheckbox140);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r156", fCheckbox156);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r172", fCheckbox172);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r188", fCheckbox188);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r204", fCheckbox204);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r220", fCheckbox220);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r236", fCheckbox236);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del12-->/r252", fCheckbox252);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r 13", fCheckbox13);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r 29", fCheckbox29);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r 45", fCheckbox45);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r 61", fCheckbox61);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r 77", fCheckbox77);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r 93", fCheckbox93);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r109", fCheckbox109);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r125", fCheckbox125);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r141", fCheckbox141);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r157", fCheckbox157);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r173", fCheckbox173);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r189", fCheckbox189);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r205", fCheckbox205);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r221", fCheckbox221);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r237", fCheckbox237);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del13-->/r253", fCheckbox253);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r 14", fCheckbox14);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r 30", fCheckbox30);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r 46", fCheckbox46);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r 62", fCheckbox62);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r 78", fCheckbox78);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r 94", fCheckbox94);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r110", fCheckbox110);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r126", fCheckbox126);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r142", fCheckbox142);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r158", fCheckbox158);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r174", fCheckbox174);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r190", fCheckbox190);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r206", fCheckbox206);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r222", fCheckbox222);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r238", fCheckbox238);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del14-->/r254", fCheckbox254);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r 15", fCheckbox15);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r 31", fCheckbox31);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r 47", fCheckbox47);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r 63", fCheckbox63);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r 79", fCheckbox79);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r 95", fCheckbox95);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r111", fCheckbox111);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r127", fCheckbox127);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r143", fCheckbox143);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r159", fCheckbox159);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r175", fCheckbox175);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r191", fCheckbox191);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r207", fCheckbox207);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r223", fCheckbox223);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r239", fCheckbox239);
	FAUST_ADDCHECKBOX("Lines/Reinjection_Matrix/Del15-->/r255", fCheckbox255);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp  0", fCheckbox336);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp 17", fCheckbox342);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp 34", fCheckbox359);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp 51", fCheckbox376);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp 68", fCheckbox393);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp 85", fCheckbox410);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp102", fCheckbox427);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp119", fCheckbox339);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp136", fCheckbox340);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp153", fCheckbox338);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 0-->/sp170", fCheckbox337);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp  1", fCheckbox326);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp 18", fCheckbox343);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp 35", fCheckbox360);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp 52", fCheckbox377);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp 69", fCheckbox394);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp 86", fCheckbox411);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp103", fCheckbox428);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp120", fCheckbox329);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp137", fCheckbox330);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp154", fCheckbox328);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 1-->/sp171", fCheckbox327);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp  2", fCheckbox321);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp 19", fCheckbox344);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp 36", fCheckbox361);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp 53", fCheckbox378);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp 70", fCheckbox395);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp 87", fCheckbox412);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp104", fCheckbox429);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp121", fCheckbox324);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp138", fCheckbox325);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp155", fCheckbox323);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 2-->/sp172", fCheckbox322);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp  3", fCheckbox316);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp 20", fCheckbox345);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp 37", fCheckbox362);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp 54", fCheckbox379);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp 71", fCheckbox396);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp 88", fCheckbox413);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp105", fCheckbox430);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp122", fCheckbox319);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp139", fCheckbox320);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp156", fCheckbox318);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 3-->/sp173", fCheckbox317);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp  4", fCheckbox311);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp 21", fCheckbox346);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp 38", fCheckbox363);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp 55", fCheckbox380);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp 72", fCheckbox397);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp 89", fCheckbox414);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp106", fCheckbox431);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp123", fCheckbox314);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp140", fCheckbox315);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp157", fCheckbox313);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 4-->/sp174", fCheckbox312);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp  5", fCheckbox306);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp 22", fCheckbox347);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp 39", fCheckbox364);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp 56", fCheckbox381);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp 73", fCheckbox398);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp 90", fCheckbox415);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp107", fCheckbox432);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp124", fCheckbox309);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp141", fCheckbox310);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp158", fCheckbox308);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 5-->/sp175", fCheckbox307);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp  6", fCheckbox301);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp 23", fCheckbox348);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp 40", fCheckbox365);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp 57", fCheckbox382);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp 74", fCheckbox399);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp 91", fCheckbox416);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp108", fCheckbox433);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp125", fCheckbox304);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp142", fCheckbox305);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp159", fCheckbox303);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 6-->/sp176", fCheckbox302);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp  7", fCheckbox296);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp 24", fCheckbox349);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp 41", fCheckbox366);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp 58", fCheckbox383);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp 75", fCheckbox400);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp 92", fCheckbox417);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp109", fCheckbox434);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp126", fCheckbox299);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp143", fCheckbox300);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp160", fCheckbox298);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 7-->/sp177", fCheckbox297);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp  8", fCheckbox291);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp 25", fCheckbox350);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp 42", fCheckbox367);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp 59", fCheckbox384);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp 76", fCheckbox401);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp 93", fCheckbox418);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp110", fCheckbox435);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp127", fCheckbox294);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp144", fCheckbox295);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp161", fCheckbox293);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 8-->/sp178", fCheckbox292);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp  9", fCheckbox286);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp 26", fCheckbox351);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp 43", fCheckbox368);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp 60", fCheckbox385);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp 77", fCheckbox402);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp 94", fCheckbox419);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp111", fCheckbox436);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp128", fCheckbox289);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp145", fCheckbox290);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp162", fCheckbox288);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig 9-->/sp179", fCheckbox287);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp 10", fCheckbox281);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp 27", fCheckbox352);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp 44", fCheckbox369);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp 61", fCheckbox386);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp 78", fCheckbox403);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp 95", fCheckbox420);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp112", fCheckbox437);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp129", fCheckbox284);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp146", fCheckbox285);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp163", fCheckbox283);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig10-->/sp180", fCheckbox282);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp 11", fCheckbox276);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp 28", fCheckbox353);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp 45", fCheckbox370);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp 62", fCheckbox387);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp 79", fCheckbox404);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp 96", fCheckbox421);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp113", fCheckbox438);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp130", fCheckbox279);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp147", fCheckbox280);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp164", fCheckbox278);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig11-->/sp181", fCheckbox277);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp 12", fCheckbox271);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp 29", fCheckbox354);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp 46", fCheckbox371);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp 63", fCheckbox388);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp 80", fCheckbox405);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp 97", fCheckbox422);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp114", fCheckbox439);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp131", fCheckbox274);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp148", fCheckbox275);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp165", fCheckbox273);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig12-->/sp182", fCheckbox272);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp 13", fCheckbox266);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp 30", fCheckbox355);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp 47", fCheckbox372);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp 64", fCheckbox389);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp 81", fCheckbox406);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp 98", fCheckbox423);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp115", fCheckbox440);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp132", fCheckbox269);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp149", fCheckbox270);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp166", fCheckbox268);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig13-->/sp183", fCheckbox267);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp 14", fCheckbox261);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp 31", fCheckbox356);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp 48", fCheckbox373);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp 65", fCheckbox390);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp 82", fCheckbox407);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp 99", fCheckbox424);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp116", fCheckbox441);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp133", fCheckbox264);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp150", fCheckbox265);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp167", fCheckbox263);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig14-->/sp184", fCheckbox262);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp 15", fCheckbox256);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp 32", fCheckbox357);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp 49", fCheckbox374);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp 66", fCheckbox391);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp 83", fCheckbox408);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp100", fCheckbox425);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp117", fCheckbox442);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp134", fCheckbox259);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp151", fCheckbox260);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp168", fCheckbox258);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig15-->/sp185", fCheckbox257);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp 16", fCheckbox331);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp 33", fCheckbox341);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp 50", fCheckbox358);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp 67", fCheckbox375);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp 84", fCheckbox392);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp101", fCheckbox409);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp118", fCheckbox426);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp135", fCheckbox334);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp152", fCheckbox335);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp169", fCheckbox333);
	FAUST_ADDCHECKBOX("Lines/SpatializationMatrix/Sig16-->/sp186", fCheckbox332);
	FAUST_ADDNUMENTRY("RandomEnv/renv_freq", fEntry0, 10.0, 0.01, 100.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("RandomEnv/renv_short", fHslider105, 0.5, 0.0, 1.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("RandomEnv/renv_trim", fHslider104, 0.0, -127.0, 18.0, 0.01);
	FAUST_ADDHORIZONTALSLIDER("a 0", fHslider103, 0.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 1", fHslider115, 45.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 2", fHslider116, 90.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 3", fHslider117, 135.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 4", fHslider118, 180.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 5", fHslider119, 225.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 6", fHslider120, 270.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("a 7", fHslider121, 315.0, -360.0, 360.0, 1.0);
	FAUST_ADDHORIZONTALSLIDER("chopan/phi0", fHslider114, 30.0, 1.0, 90.0, 1.0);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, rotfreq0, "Encoders/rotfreq0", fHslider113, 0.10000000000000001, -10.0, 10.0, 0.01) \
		p(HORIZONTALSLIDER, rotfreq1, "Encoders/rotfreq1", fHslider111, 0.10000000000000001, -10.0, 10.0, 0.01) \
		p(HORIZONTALSLIDER, rotfreq2, "Encoders/rotfreq2", fHslider109, 0.10000000000000001, -10.0, 10.0, 0.01) \
		p(HORIZONTALSLIDER, rotfreq3, "Encoders/rotfreq3", fHslider107, 0.10000000000000001, -10.0, 10.0, 0.01) \
		p(HORIZONTALSLIDER, rotphase0, "Encoders/rotphase0", fHslider112, 0.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, rotphase1, "Encoders/rotphase1", fHslider110, 0.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, rotphase2, "Encoders/rotphase2", fHslider108, 0.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, rotphase3, "Encoders/rotphase3", fHslider106, 0.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, dStretch, "Global_Parameters/dStretch", fHslider36, 1.0, 0.01, 10.0, 0.01) \
		p(HORIZONTALSLIDER, delharmoGain, "Global_Parameters/delharmoGain", fHslider35, 0.0, -127.0, 18.0, 0.01) \
		p(HORIZONTALSLIDER, generalGain, "Global_Parameters/generalGain", fHslider0, 0.0, -127.0, 18.0, 0.01) \
		p(HORIZONTALSLIDER, guitarGain, "Global_Parameters/guitarGain", fHslider101, -34.0, -127.0, 18.0, 0.01) \
		p(HORIZONTALSLIDER, hStretch, "Global_Parameters/hStretch", fHslider38, 1.0, -10.0, 10.0, 0.01) \
		p(HORIZONTALSLIDER, hWin, "Global_Parameters/hWin", fHslider40, 64.0, 1.0, 127.0, 0.01) \
		p(HORIZONTALSLIDER, smoothDuration, "Global_Parameters/smoothDuration", fHslider1, 20.0, 10.0, 5000.0, 1.0) \
		p(HORIZONTALSLIDER, d_0, "Lines/Del_Durations/d 0", fHslider37, 100.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_1, "Lines/Del_Durations/d 1", fHslider42, 200.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_2, "Lines/Del_Durations/d 2", fHslider45, 300.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_3, "Lines/Del_Durations/d 3", fHslider48, 400.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_4, "Lines/Del_Durations/d 4", fHslider51, 500.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_5, "Lines/Del_Durations/d 5", fHslider54, 600.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_6, "Lines/Del_Durations/d 6", fHslider57, 700.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_7, "Lines/Del_Durations/d 7", fHslider60, 800.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_8, "Lines/Del_Durations/d 8", fHslider63, 900.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d_9, "Lines/Del_Durations/d 9", fHslider66, 1000.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d10, "Lines/Del_Durations/d10", fHslider69, 1100.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d11, "Lines/Del_Durations/d11", fHslider72, 1200.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d12, "Lines/Del_Durations/d12", fHslider75, 1300.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d13, "Lines/Del_Durations/d13", fHslider78, 1400.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d14, "Lines/Del_Durations/d14", fHslider81, 1500.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, d15, "Lines/Del_Durations/d15", fHslider84, 1600.0, 0.0, 21000.0, 1.0) \
		p(HORIZONTALSLIDER, fd_0, "Lines/Del_Feedbacks/fd 0", fHslider3, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_1, "Lines/Del_Feedbacks/fd 1", fHslider5, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_2, "Lines/Del_Feedbacks/fd 2", fHslider7, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_3, "Lines/Del_Feedbacks/fd 3", fHslider9, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_4, "Lines/Del_Feedbacks/fd 4", fHslider11, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_5, "Lines/Del_Feedbacks/fd 5", fHslider13, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_6, "Lines/Del_Feedbacks/fd 6", fHslider15, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_7, "Lines/Del_Feedbacks/fd 7", fHslider17, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_8, "Lines/Del_Feedbacks/fd 8", fHslider19, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd_9, "Lines/Del_Feedbacks/fd 9", fHslider21, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd10, "Lines/Del_Feedbacks/fd10", fHslider23, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd11, "Lines/Del_Feedbacks/fd11", fHslider25, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd12, "Lines/Del_Feedbacks/fd12", fHslider27, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd13, "Lines/Del_Feedbacks/fd13", fHslider29, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd14, "Lines/Del_Feedbacks/fd14", fHslider31, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, fd15, "Lines/Del_Feedbacks/fd15", fHslider33, 0.0, 0.0, 0.98999999999999999, 0.01) \
		p(HORIZONTALSLIDER, xvd_0, "Lines/EffeX_vs_Del/xvd 0", fHslider2, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_1, "Lines/EffeX_vs_Del/xvd 1", fHslider4, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_2, "Lines/EffeX_vs_Del/xvd 2", fHslider6, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_3, "Lines/EffeX_vs_Del/xvd 3", fHslider8, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_4, "Lines/EffeX_vs_Del/xvd 4", fHslider10, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_5, "Lines/EffeX_vs_Del/xvd 5", fHslider12, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_6, "Lines/EffeX_vs_Del/xvd 6", fHslider14, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_7, "Lines/EffeX_vs_Del/xvd 7", fHslider16, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_8, "Lines/EffeX_vs_Del/xvd 8", fHslider18, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd_9, "Lines/EffeX_vs_Del/xvd 9", fHslider20, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd10, "Lines/EffeX_vs_Del/xvd10", fHslider22, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd11, "Lines/EffeX_vs_Del/xvd11", fHslider24, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd12, "Lines/EffeX_vs_Del/xvd12", fHslider26, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd13, "Lines/EffeX_vs_Del/xvd13", fHslider28, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd14, "Lines/EffeX_vs_Del/xvd14", fHslider30, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, xvd15, "Lines/EffeX_vs_Del/xvd15", fHslider32, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, tr_0, "Lines/Harmo_Transpositions/tr 0", fHslider39, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_1, "Lines/Harmo_Transpositions/tr 1", fHslider43, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_2, "Lines/Harmo_Transpositions/tr 2", fHslider46, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_3, "Lines/Harmo_Transpositions/tr 3", fHslider49, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_4, "Lines/Harmo_Transpositions/tr 4", fHslider52, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_5, "Lines/Harmo_Transpositions/tr 5", fHslider55, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_6, "Lines/Harmo_Transpositions/tr 6", fHslider58, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_7, "Lines/Harmo_Transpositions/tr 7", fHslider61, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_8, "Lines/Harmo_Transpositions/tr 8", fHslider64, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr_9, "Lines/Harmo_Transpositions/tr 9", fHslider67, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr10, "Lines/Harmo_Transpositions/tr10", fHslider70, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr11, "Lines/Harmo_Transpositions/tr11", fHslider73, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr12, "Lines/Harmo_Transpositions/tr12", fHslider76, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr13, "Lines/Harmo_Transpositions/tr13", fHslider79, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr14, "Lines/Harmo_Transpositions/tr14", fHslider82, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, tr15, "Lines/Harmo_Transpositions/tr15", fHslider85, 0.0, -2400.0, 2400.0, 1.0) \
		p(HORIZONTALSLIDER, inp_0, "Lines/Line_input/inp 0", fHslider34, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_1, "Lines/Line_input/inp 1", fHslider41, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_2, "Lines/Line_input/inp 2", fHslider44, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_3, "Lines/Line_input/inp 3", fHslider47, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_4, "Lines/Line_input/inp 4", fHslider50, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_5, "Lines/Line_input/inp 5", fHslider53, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_6, "Lines/Line_input/inp 6", fHslider56, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_7, "Lines/Line_input/inp 7", fHslider59, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_8, "Lines/Line_input/inp 8", fHslider62, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp_9, "Lines/Line_input/inp 9", fHslider65, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp10, "Lines/Line_input/inp10", fHslider68, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp11, "Lines/Line_input/inp11", fHslider71, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp12, "Lines/Line_input/inp12", fHslider74, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp13, "Lines/Line_input/inp13", fHslider77, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp14, "Lines/Line_input/inp14", fHslider80, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, inp15, "Lines/Line_input/inp15", fHslider83, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_0, "Lines/Line_output/out 0", fHslider102, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_1, "Lines/Line_output/out 1", fHslider100, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_2, "Lines/Line_output/out 2", fHslider99, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_3, "Lines/Line_output/out 3", fHslider98, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_4, "Lines/Line_output/out 4", fHslider97, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_5, "Lines/Line_output/out 5", fHslider96, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_6, "Lines/Line_output/out 6", fHslider95, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_7, "Lines/Line_output/out 7", fHslider94, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_8, "Lines/Line_output/out 8", fHslider93, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out_9, "Lines/Line_output/out 9", fHslider92, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out10, "Lines/Line_output/out10", fHslider91, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out11, "Lines/Line_output/out11", fHslider90, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out12, "Lines/Line_output/out12", fHslider89, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out13, "Lines/Line_output/out13", fHslider88, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out14, "Lines/Line_output/out14", fHslider87, 1.0, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, out15, "Lines/Line_output/out15", fHslider86, 1.0, 0.0, 1.0, 0.01) \
		p(CHECKBOX, r__0, "Lines/Reinjection_Matrix/Del 0-->/r  0", fCheckbox0, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_16, "Lines/Reinjection_Matrix/Del 0-->/r 16", fCheckbox16, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_32, "Lines/Reinjection_Matrix/Del 0-->/r 32", fCheckbox32, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_48, "Lines/Reinjection_Matrix/Del 0-->/r 48", fCheckbox48, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_64, "Lines/Reinjection_Matrix/Del 0-->/r 64", fCheckbox64, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_80, "Lines/Reinjection_Matrix/Del 0-->/r 80", fCheckbox80, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_96, "Lines/Reinjection_Matrix/Del 0-->/r 96", fCheckbox96, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r112, "Lines/Reinjection_Matrix/Del 0-->/r112", fCheckbox112, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r128, "Lines/Reinjection_Matrix/Del 0-->/r128", fCheckbox128, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r144, "Lines/Reinjection_Matrix/Del 0-->/r144", fCheckbox144, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r160, "Lines/Reinjection_Matrix/Del 0-->/r160", fCheckbox160, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r176, "Lines/Reinjection_Matrix/Del 0-->/r176", fCheckbox176, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r192, "Lines/Reinjection_Matrix/Del 0-->/r192", fCheckbox192, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r208, "Lines/Reinjection_Matrix/Del 0-->/r208", fCheckbox208, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r224, "Lines/Reinjection_Matrix/Del 0-->/r224", fCheckbox224, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r240, "Lines/Reinjection_Matrix/Del 0-->/r240", fCheckbox240, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__1, "Lines/Reinjection_Matrix/Del 1-->/r  1", fCheckbox1, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_17, "Lines/Reinjection_Matrix/Del 1-->/r 17", fCheckbox17, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_33, "Lines/Reinjection_Matrix/Del 1-->/r 33", fCheckbox33, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_49, "Lines/Reinjection_Matrix/Del 1-->/r 49", fCheckbox49, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_65, "Lines/Reinjection_Matrix/Del 1-->/r 65", fCheckbox65, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_81, "Lines/Reinjection_Matrix/Del 1-->/r 81", fCheckbox81, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_97, "Lines/Reinjection_Matrix/Del 1-->/r 97", fCheckbox97, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r113, "Lines/Reinjection_Matrix/Del 1-->/r113", fCheckbox113, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r129, "Lines/Reinjection_Matrix/Del 1-->/r129", fCheckbox129, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r145, "Lines/Reinjection_Matrix/Del 1-->/r145", fCheckbox145, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r161, "Lines/Reinjection_Matrix/Del 1-->/r161", fCheckbox161, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r177, "Lines/Reinjection_Matrix/Del 1-->/r177", fCheckbox177, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r193, "Lines/Reinjection_Matrix/Del 1-->/r193", fCheckbox193, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r209, "Lines/Reinjection_Matrix/Del 1-->/r209", fCheckbox209, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r225, "Lines/Reinjection_Matrix/Del 1-->/r225", fCheckbox225, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r241, "Lines/Reinjection_Matrix/Del 1-->/r241", fCheckbox241, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__2, "Lines/Reinjection_Matrix/Del 2-->/r  2", fCheckbox2, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_18, "Lines/Reinjection_Matrix/Del 2-->/r 18", fCheckbox18, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_34, "Lines/Reinjection_Matrix/Del 2-->/r 34", fCheckbox34, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_50, "Lines/Reinjection_Matrix/Del 2-->/r 50", fCheckbox50, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_66, "Lines/Reinjection_Matrix/Del 2-->/r 66", fCheckbox66, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_82, "Lines/Reinjection_Matrix/Del 2-->/r 82", fCheckbox82, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_98, "Lines/Reinjection_Matrix/Del 2-->/r 98", fCheckbox98, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r114, "Lines/Reinjection_Matrix/Del 2-->/r114", fCheckbox114, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r130, "Lines/Reinjection_Matrix/Del 2-->/r130", fCheckbox130, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r146, "Lines/Reinjection_Matrix/Del 2-->/r146", fCheckbox146, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r162, "Lines/Reinjection_Matrix/Del 2-->/r162", fCheckbox162, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r178, "Lines/Reinjection_Matrix/Del 2-->/r178", fCheckbox178, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r194, "Lines/Reinjection_Matrix/Del 2-->/r194", fCheckbox194, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r210, "Lines/Reinjection_Matrix/Del 2-->/r210", fCheckbox210, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r226, "Lines/Reinjection_Matrix/Del 2-->/r226", fCheckbox226, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r242, "Lines/Reinjection_Matrix/Del 2-->/r242", fCheckbox242, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__3, "Lines/Reinjection_Matrix/Del 3-->/r  3", fCheckbox3, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_19, "Lines/Reinjection_Matrix/Del 3-->/r 19", fCheckbox19, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_35, "Lines/Reinjection_Matrix/Del 3-->/r 35", fCheckbox35, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_51, "Lines/Reinjection_Matrix/Del 3-->/r 51", fCheckbox51, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_67, "Lines/Reinjection_Matrix/Del 3-->/r 67", fCheckbox67, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_83, "Lines/Reinjection_Matrix/Del 3-->/r 83", fCheckbox83, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_99, "Lines/Reinjection_Matrix/Del 3-->/r 99", fCheckbox99, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r115, "Lines/Reinjection_Matrix/Del 3-->/r115", fCheckbox115, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r131, "Lines/Reinjection_Matrix/Del 3-->/r131", fCheckbox131, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r147, "Lines/Reinjection_Matrix/Del 3-->/r147", fCheckbox147, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r163, "Lines/Reinjection_Matrix/Del 3-->/r163", fCheckbox163, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r179, "Lines/Reinjection_Matrix/Del 3-->/r179", fCheckbox179, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r195, "Lines/Reinjection_Matrix/Del 3-->/r195", fCheckbox195, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r211, "Lines/Reinjection_Matrix/Del 3-->/r211", fCheckbox211, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r227, "Lines/Reinjection_Matrix/Del 3-->/r227", fCheckbox227, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r243, "Lines/Reinjection_Matrix/Del 3-->/r243", fCheckbox243, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__4, "Lines/Reinjection_Matrix/Del 4-->/r  4", fCheckbox4, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_20, "Lines/Reinjection_Matrix/Del 4-->/r 20", fCheckbox20, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_36, "Lines/Reinjection_Matrix/Del 4-->/r 36", fCheckbox36, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_52, "Lines/Reinjection_Matrix/Del 4-->/r 52", fCheckbox52, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_68, "Lines/Reinjection_Matrix/Del 4-->/r 68", fCheckbox68, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_84, "Lines/Reinjection_Matrix/Del 4-->/r 84", fCheckbox84, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r100, "Lines/Reinjection_Matrix/Del 4-->/r100", fCheckbox100, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r116, "Lines/Reinjection_Matrix/Del 4-->/r116", fCheckbox116, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r132, "Lines/Reinjection_Matrix/Del 4-->/r132", fCheckbox132, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r148, "Lines/Reinjection_Matrix/Del 4-->/r148", fCheckbox148, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r164, "Lines/Reinjection_Matrix/Del 4-->/r164", fCheckbox164, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r180, "Lines/Reinjection_Matrix/Del 4-->/r180", fCheckbox180, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r196, "Lines/Reinjection_Matrix/Del 4-->/r196", fCheckbox196, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r212, "Lines/Reinjection_Matrix/Del 4-->/r212", fCheckbox212, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r228, "Lines/Reinjection_Matrix/Del 4-->/r228", fCheckbox228, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r244, "Lines/Reinjection_Matrix/Del 4-->/r244", fCheckbox244, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__5, "Lines/Reinjection_Matrix/Del 5-->/r  5", fCheckbox5, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_21, "Lines/Reinjection_Matrix/Del 5-->/r 21", fCheckbox21, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_37, "Lines/Reinjection_Matrix/Del 5-->/r 37", fCheckbox37, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_53, "Lines/Reinjection_Matrix/Del 5-->/r 53", fCheckbox53, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_69, "Lines/Reinjection_Matrix/Del 5-->/r 69", fCheckbox69, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_85, "Lines/Reinjection_Matrix/Del 5-->/r 85", fCheckbox85, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r101, "Lines/Reinjection_Matrix/Del 5-->/r101", fCheckbox101, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r117, "Lines/Reinjection_Matrix/Del 5-->/r117", fCheckbox117, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r133, "Lines/Reinjection_Matrix/Del 5-->/r133", fCheckbox133, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r149, "Lines/Reinjection_Matrix/Del 5-->/r149", fCheckbox149, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r165, "Lines/Reinjection_Matrix/Del 5-->/r165", fCheckbox165, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r181, "Lines/Reinjection_Matrix/Del 5-->/r181", fCheckbox181, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r197, "Lines/Reinjection_Matrix/Del 5-->/r197", fCheckbox197, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r213, "Lines/Reinjection_Matrix/Del 5-->/r213", fCheckbox213, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r229, "Lines/Reinjection_Matrix/Del 5-->/r229", fCheckbox229, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r245, "Lines/Reinjection_Matrix/Del 5-->/r245", fCheckbox245, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__6, "Lines/Reinjection_Matrix/Del 6-->/r  6", fCheckbox6, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_22, "Lines/Reinjection_Matrix/Del 6-->/r 22", fCheckbox22, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_38, "Lines/Reinjection_Matrix/Del 6-->/r 38", fCheckbox38, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_54, "Lines/Reinjection_Matrix/Del 6-->/r 54", fCheckbox54, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_70, "Lines/Reinjection_Matrix/Del 6-->/r 70", fCheckbox70, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_86, "Lines/Reinjection_Matrix/Del 6-->/r 86", fCheckbox86, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r102, "Lines/Reinjection_Matrix/Del 6-->/r102", fCheckbox102, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r118, "Lines/Reinjection_Matrix/Del 6-->/r118", fCheckbox118, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r134, "Lines/Reinjection_Matrix/Del 6-->/r134", fCheckbox134, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r150, "Lines/Reinjection_Matrix/Del 6-->/r150", fCheckbox150, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r166, "Lines/Reinjection_Matrix/Del 6-->/r166", fCheckbox166, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r182, "Lines/Reinjection_Matrix/Del 6-->/r182", fCheckbox182, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r198, "Lines/Reinjection_Matrix/Del 6-->/r198", fCheckbox198, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r214, "Lines/Reinjection_Matrix/Del 6-->/r214", fCheckbox214, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r230, "Lines/Reinjection_Matrix/Del 6-->/r230", fCheckbox230, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r246, "Lines/Reinjection_Matrix/Del 6-->/r246", fCheckbox246, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__7, "Lines/Reinjection_Matrix/Del 7-->/r  7", fCheckbox7, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_23, "Lines/Reinjection_Matrix/Del 7-->/r 23", fCheckbox23, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_39, "Lines/Reinjection_Matrix/Del 7-->/r 39", fCheckbox39, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_55, "Lines/Reinjection_Matrix/Del 7-->/r 55", fCheckbox55, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_71, "Lines/Reinjection_Matrix/Del 7-->/r 71", fCheckbox71, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_87, "Lines/Reinjection_Matrix/Del 7-->/r 87", fCheckbox87, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r103, "Lines/Reinjection_Matrix/Del 7-->/r103", fCheckbox103, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r119, "Lines/Reinjection_Matrix/Del 7-->/r119", fCheckbox119, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r135, "Lines/Reinjection_Matrix/Del 7-->/r135", fCheckbox135, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r151, "Lines/Reinjection_Matrix/Del 7-->/r151", fCheckbox151, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r167, "Lines/Reinjection_Matrix/Del 7-->/r167", fCheckbox167, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r183, "Lines/Reinjection_Matrix/Del 7-->/r183", fCheckbox183, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r199, "Lines/Reinjection_Matrix/Del 7-->/r199", fCheckbox199, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r215, "Lines/Reinjection_Matrix/Del 7-->/r215", fCheckbox215, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r231, "Lines/Reinjection_Matrix/Del 7-->/r231", fCheckbox231, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r247, "Lines/Reinjection_Matrix/Del 7-->/r247", fCheckbox247, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__8, "Lines/Reinjection_Matrix/Del 8-->/r  8", fCheckbox8, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_24, "Lines/Reinjection_Matrix/Del 8-->/r 24", fCheckbox24, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_40, "Lines/Reinjection_Matrix/Del 8-->/r 40", fCheckbox40, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_56, "Lines/Reinjection_Matrix/Del 8-->/r 56", fCheckbox56, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_72, "Lines/Reinjection_Matrix/Del 8-->/r 72", fCheckbox72, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_88, "Lines/Reinjection_Matrix/Del 8-->/r 88", fCheckbox88, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r104, "Lines/Reinjection_Matrix/Del 8-->/r104", fCheckbox104, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r120, "Lines/Reinjection_Matrix/Del 8-->/r120", fCheckbox120, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r136, "Lines/Reinjection_Matrix/Del 8-->/r136", fCheckbox136, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r152, "Lines/Reinjection_Matrix/Del 8-->/r152", fCheckbox152, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r168, "Lines/Reinjection_Matrix/Del 8-->/r168", fCheckbox168, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r184, "Lines/Reinjection_Matrix/Del 8-->/r184", fCheckbox184, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r200, "Lines/Reinjection_Matrix/Del 8-->/r200", fCheckbox200, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r216, "Lines/Reinjection_Matrix/Del 8-->/r216", fCheckbox216, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r232, "Lines/Reinjection_Matrix/Del 8-->/r232", fCheckbox232, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r248, "Lines/Reinjection_Matrix/Del 8-->/r248", fCheckbox248, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r__9, "Lines/Reinjection_Matrix/Del 9-->/r  9", fCheckbox9, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_25, "Lines/Reinjection_Matrix/Del 9-->/r 25", fCheckbox25, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_41, "Lines/Reinjection_Matrix/Del 9-->/r 41", fCheckbox41, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_57, "Lines/Reinjection_Matrix/Del 9-->/r 57", fCheckbox57, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_73, "Lines/Reinjection_Matrix/Del 9-->/r 73", fCheckbox73, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_89, "Lines/Reinjection_Matrix/Del 9-->/r 89", fCheckbox89, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r105, "Lines/Reinjection_Matrix/Del 9-->/r105", fCheckbox105, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r121, "Lines/Reinjection_Matrix/Del 9-->/r121", fCheckbox121, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r137, "Lines/Reinjection_Matrix/Del 9-->/r137", fCheckbox137, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r153, "Lines/Reinjection_Matrix/Del 9-->/r153", fCheckbox153, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r169, "Lines/Reinjection_Matrix/Del 9-->/r169", fCheckbox169, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r185, "Lines/Reinjection_Matrix/Del 9-->/r185", fCheckbox185, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r201, "Lines/Reinjection_Matrix/Del 9-->/r201", fCheckbox201, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r217, "Lines/Reinjection_Matrix/Del 9-->/r217", fCheckbox217, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r233, "Lines/Reinjection_Matrix/Del 9-->/r233", fCheckbox233, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r249, "Lines/Reinjection_Matrix/Del 9-->/r249", fCheckbox249, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_10, "Lines/Reinjection_Matrix/Del10-->/r 10", fCheckbox10, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_26, "Lines/Reinjection_Matrix/Del10-->/r 26", fCheckbox26, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_42, "Lines/Reinjection_Matrix/Del10-->/r 42", fCheckbox42, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_58, "Lines/Reinjection_Matrix/Del10-->/r 58", fCheckbox58, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_74, "Lines/Reinjection_Matrix/Del10-->/r 74", fCheckbox74, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_90, "Lines/Reinjection_Matrix/Del10-->/r 90", fCheckbox90, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r106, "Lines/Reinjection_Matrix/Del10-->/r106", fCheckbox106, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r122, "Lines/Reinjection_Matrix/Del10-->/r122", fCheckbox122, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r138, "Lines/Reinjection_Matrix/Del10-->/r138", fCheckbox138, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r154, "Lines/Reinjection_Matrix/Del10-->/r154", fCheckbox154, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r170, "Lines/Reinjection_Matrix/Del10-->/r170", fCheckbox170, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r186, "Lines/Reinjection_Matrix/Del10-->/r186", fCheckbox186, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r202, "Lines/Reinjection_Matrix/Del10-->/r202", fCheckbox202, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r218, "Lines/Reinjection_Matrix/Del10-->/r218", fCheckbox218, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r234, "Lines/Reinjection_Matrix/Del10-->/r234", fCheckbox234, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r250, "Lines/Reinjection_Matrix/Del10-->/r250", fCheckbox250, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_11, "Lines/Reinjection_Matrix/Del11-->/r 11", fCheckbox11, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_27, "Lines/Reinjection_Matrix/Del11-->/r 27", fCheckbox27, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_43, "Lines/Reinjection_Matrix/Del11-->/r 43", fCheckbox43, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_59, "Lines/Reinjection_Matrix/Del11-->/r 59", fCheckbox59, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_75, "Lines/Reinjection_Matrix/Del11-->/r 75", fCheckbox75, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_91, "Lines/Reinjection_Matrix/Del11-->/r 91", fCheckbox91, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r107, "Lines/Reinjection_Matrix/Del11-->/r107", fCheckbox107, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r123, "Lines/Reinjection_Matrix/Del11-->/r123", fCheckbox123, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r139, "Lines/Reinjection_Matrix/Del11-->/r139", fCheckbox139, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r155, "Lines/Reinjection_Matrix/Del11-->/r155", fCheckbox155, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r171, "Lines/Reinjection_Matrix/Del11-->/r171", fCheckbox171, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r187, "Lines/Reinjection_Matrix/Del11-->/r187", fCheckbox187, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r203, "Lines/Reinjection_Matrix/Del11-->/r203", fCheckbox203, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r219, "Lines/Reinjection_Matrix/Del11-->/r219", fCheckbox219, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r235, "Lines/Reinjection_Matrix/Del11-->/r235", fCheckbox235, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r251, "Lines/Reinjection_Matrix/Del11-->/r251", fCheckbox251, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_12, "Lines/Reinjection_Matrix/Del12-->/r 12", fCheckbox12, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_28, "Lines/Reinjection_Matrix/Del12-->/r 28", fCheckbox28, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_44, "Lines/Reinjection_Matrix/Del12-->/r 44", fCheckbox44, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_60, "Lines/Reinjection_Matrix/Del12-->/r 60", fCheckbox60, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_76, "Lines/Reinjection_Matrix/Del12-->/r 76", fCheckbox76, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_92, "Lines/Reinjection_Matrix/Del12-->/r 92", fCheckbox92, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r108, "Lines/Reinjection_Matrix/Del12-->/r108", fCheckbox108, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r124, "Lines/Reinjection_Matrix/Del12-->/r124", fCheckbox124, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r140, "Lines/Reinjection_Matrix/Del12-->/r140", fCheckbox140, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r156, "Lines/Reinjection_Matrix/Del12-->/r156", fCheckbox156, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r172, "Lines/Reinjection_Matrix/Del12-->/r172", fCheckbox172, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r188, "Lines/Reinjection_Matrix/Del12-->/r188", fCheckbox188, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r204, "Lines/Reinjection_Matrix/Del12-->/r204", fCheckbox204, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r220, "Lines/Reinjection_Matrix/Del12-->/r220", fCheckbox220, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r236, "Lines/Reinjection_Matrix/Del12-->/r236", fCheckbox236, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r252, "Lines/Reinjection_Matrix/Del12-->/r252", fCheckbox252, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_13, "Lines/Reinjection_Matrix/Del13-->/r 13", fCheckbox13, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_29, "Lines/Reinjection_Matrix/Del13-->/r 29", fCheckbox29, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_45, "Lines/Reinjection_Matrix/Del13-->/r 45", fCheckbox45, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_61, "Lines/Reinjection_Matrix/Del13-->/r 61", fCheckbox61, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_77, "Lines/Reinjection_Matrix/Del13-->/r 77", fCheckbox77, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_93, "Lines/Reinjection_Matrix/Del13-->/r 93", fCheckbox93, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r109, "Lines/Reinjection_Matrix/Del13-->/r109", fCheckbox109, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r125, "Lines/Reinjection_Matrix/Del13-->/r125", fCheckbox125, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r141, "Lines/Reinjection_Matrix/Del13-->/r141", fCheckbox141, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r157, "Lines/Reinjection_Matrix/Del13-->/r157", fCheckbox157, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r173, "Lines/Reinjection_Matrix/Del13-->/r173", fCheckbox173, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r189, "Lines/Reinjection_Matrix/Del13-->/r189", fCheckbox189, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r205, "Lines/Reinjection_Matrix/Del13-->/r205", fCheckbox205, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r221, "Lines/Reinjection_Matrix/Del13-->/r221", fCheckbox221, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r237, "Lines/Reinjection_Matrix/Del13-->/r237", fCheckbox237, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r253, "Lines/Reinjection_Matrix/Del13-->/r253", fCheckbox253, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_14, "Lines/Reinjection_Matrix/Del14-->/r 14", fCheckbox14, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_30, "Lines/Reinjection_Matrix/Del14-->/r 30", fCheckbox30, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_46, "Lines/Reinjection_Matrix/Del14-->/r 46", fCheckbox46, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_62, "Lines/Reinjection_Matrix/Del14-->/r 62", fCheckbox62, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_78, "Lines/Reinjection_Matrix/Del14-->/r 78", fCheckbox78, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_94, "Lines/Reinjection_Matrix/Del14-->/r 94", fCheckbox94, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r110, "Lines/Reinjection_Matrix/Del14-->/r110", fCheckbox110, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r126, "Lines/Reinjection_Matrix/Del14-->/r126", fCheckbox126, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r142, "Lines/Reinjection_Matrix/Del14-->/r142", fCheckbox142, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r158, "Lines/Reinjection_Matrix/Del14-->/r158", fCheckbox158, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r174, "Lines/Reinjection_Matrix/Del14-->/r174", fCheckbox174, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r190, "Lines/Reinjection_Matrix/Del14-->/r190", fCheckbox190, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r206, "Lines/Reinjection_Matrix/Del14-->/r206", fCheckbox206, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r222, "Lines/Reinjection_Matrix/Del14-->/r222", fCheckbox222, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r238, "Lines/Reinjection_Matrix/Del14-->/r238", fCheckbox238, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r254, "Lines/Reinjection_Matrix/Del14-->/r254", fCheckbox254, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_15, "Lines/Reinjection_Matrix/Del15-->/r 15", fCheckbox15, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_31, "Lines/Reinjection_Matrix/Del15-->/r 31", fCheckbox31, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_47, "Lines/Reinjection_Matrix/Del15-->/r 47", fCheckbox47, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_63, "Lines/Reinjection_Matrix/Del15-->/r 63", fCheckbox63, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_79, "Lines/Reinjection_Matrix/Del15-->/r 79", fCheckbox79, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r_95, "Lines/Reinjection_Matrix/Del15-->/r 95", fCheckbox95, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r111, "Lines/Reinjection_Matrix/Del15-->/r111", fCheckbox111, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r127, "Lines/Reinjection_Matrix/Del15-->/r127", fCheckbox127, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r143, "Lines/Reinjection_Matrix/Del15-->/r143", fCheckbox143, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r159, "Lines/Reinjection_Matrix/Del15-->/r159", fCheckbox159, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r175, "Lines/Reinjection_Matrix/Del15-->/r175", fCheckbox175, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r191, "Lines/Reinjection_Matrix/Del15-->/r191", fCheckbox191, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r207, "Lines/Reinjection_Matrix/Del15-->/r207", fCheckbox207, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r223, "Lines/Reinjection_Matrix/Del15-->/r223", fCheckbox223, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r239, "Lines/Reinjection_Matrix/Del15-->/r239", fCheckbox239, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, r255, "Lines/Reinjection_Matrix/Del15-->/r255", fCheckbox255, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__0, "Lines/SpatializationMatrix/Sig 0-->/sp  0", fCheckbox336, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_17, "Lines/SpatializationMatrix/Sig 0-->/sp 17", fCheckbox342, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_34, "Lines/SpatializationMatrix/Sig 0-->/sp 34", fCheckbox359, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_51, "Lines/SpatializationMatrix/Sig 0-->/sp 51", fCheckbox376, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_68, "Lines/SpatializationMatrix/Sig 0-->/sp 68", fCheckbox393, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_85, "Lines/SpatializationMatrix/Sig 0-->/sp 85", fCheckbox410, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp102, "Lines/SpatializationMatrix/Sig 0-->/sp102", fCheckbox427, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp119, "Lines/SpatializationMatrix/Sig 0-->/sp119", fCheckbox339, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp136, "Lines/SpatializationMatrix/Sig 0-->/sp136", fCheckbox340, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp153, "Lines/SpatializationMatrix/Sig 0-->/sp153", fCheckbox338, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp170, "Lines/SpatializationMatrix/Sig 0-->/sp170", fCheckbox337, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__1, "Lines/SpatializationMatrix/Sig 1-->/sp  1", fCheckbox326, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_18, "Lines/SpatializationMatrix/Sig 1-->/sp 18", fCheckbox343, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_35, "Lines/SpatializationMatrix/Sig 1-->/sp 35", fCheckbox360, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_52, "Lines/SpatializationMatrix/Sig 1-->/sp 52", fCheckbox377, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_69, "Lines/SpatializationMatrix/Sig 1-->/sp 69", fCheckbox394, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_86, "Lines/SpatializationMatrix/Sig 1-->/sp 86", fCheckbox411, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp103, "Lines/SpatializationMatrix/Sig 1-->/sp103", fCheckbox428, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp120, "Lines/SpatializationMatrix/Sig 1-->/sp120", fCheckbox329, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp137, "Lines/SpatializationMatrix/Sig 1-->/sp137", fCheckbox330, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp154, "Lines/SpatializationMatrix/Sig 1-->/sp154", fCheckbox328, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp171, "Lines/SpatializationMatrix/Sig 1-->/sp171", fCheckbox327, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__2, "Lines/SpatializationMatrix/Sig 2-->/sp  2", fCheckbox321, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_19, "Lines/SpatializationMatrix/Sig 2-->/sp 19", fCheckbox344, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_36, "Lines/SpatializationMatrix/Sig 2-->/sp 36", fCheckbox361, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_53, "Lines/SpatializationMatrix/Sig 2-->/sp 53", fCheckbox378, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_70, "Lines/SpatializationMatrix/Sig 2-->/sp 70", fCheckbox395, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_87, "Lines/SpatializationMatrix/Sig 2-->/sp 87", fCheckbox412, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp104, "Lines/SpatializationMatrix/Sig 2-->/sp104", fCheckbox429, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp121, "Lines/SpatializationMatrix/Sig 2-->/sp121", fCheckbox324, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp138, "Lines/SpatializationMatrix/Sig 2-->/sp138", fCheckbox325, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp155, "Lines/SpatializationMatrix/Sig 2-->/sp155", fCheckbox323, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp172, "Lines/SpatializationMatrix/Sig 2-->/sp172", fCheckbox322, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__3, "Lines/SpatializationMatrix/Sig 3-->/sp  3", fCheckbox316, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_20, "Lines/SpatializationMatrix/Sig 3-->/sp 20", fCheckbox345, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_37, "Lines/SpatializationMatrix/Sig 3-->/sp 37", fCheckbox362, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_54, "Lines/SpatializationMatrix/Sig 3-->/sp 54", fCheckbox379, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_71, "Lines/SpatializationMatrix/Sig 3-->/sp 71", fCheckbox396, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_88, "Lines/SpatializationMatrix/Sig 3-->/sp 88", fCheckbox413, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp105, "Lines/SpatializationMatrix/Sig 3-->/sp105", fCheckbox430, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp122, "Lines/SpatializationMatrix/Sig 3-->/sp122", fCheckbox319, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp139, "Lines/SpatializationMatrix/Sig 3-->/sp139", fCheckbox320, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp156, "Lines/SpatializationMatrix/Sig 3-->/sp156", fCheckbox318, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp173, "Lines/SpatializationMatrix/Sig 3-->/sp173", fCheckbox317, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__4, "Lines/SpatializationMatrix/Sig 4-->/sp  4", fCheckbox311, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_21, "Lines/SpatializationMatrix/Sig 4-->/sp 21", fCheckbox346, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_38, "Lines/SpatializationMatrix/Sig 4-->/sp 38", fCheckbox363, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_55, "Lines/SpatializationMatrix/Sig 4-->/sp 55", fCheckbox380, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_72, "Lines/SpatializationMatrix/Sig 4-->/sp 72", fCheckbox397, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_89, "Lines/SpatializationMatrix/Sig 4-->/sp 89", fCheckbox414, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp106, "Lines/SpatializationMatrix/Sig 4-->/sp106", fCheckbox431, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp123, "Lines/SpatializationMatrix/Sig 4-->/sp123", fCheckbox314, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp140, "Lines/SpatializationMatrix/Sig 4-->/sp140", fCheckbox315, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp157, "Lines/SpatializationMatrix/Sig 4-->/sp157", fCheckbox313, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp174, "Lines/SpatializationMatrix/Sig 4-->/sp174", fCheckbox312, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__5, "Lines/SpatializationMatrix/Sig 5-->/sp  5", fCheckbox306, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_22, "Lines/SpatializationMatrix/Sig 5-->/sp 22", fCheckbox347, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_39, "Lines/SpatializationMatrix/Sig 5-->/sp 39", fCheckbox364, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_56, "Lines/SpatializationMatrix/Sig 5-->/sp 56", fCheckbox381, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_73, "Lines/SpatializationMatrix/Sig 5-->/sp 73", fCheckbox398, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_90, "Lines/SpatializationMatrix/Sig 5-->/sp 90", fCheckbox415, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp107, "Lines/SpatializationMatrix/Sig 5-->/sp107", fCheckbox432, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp124, "Lines/SpatializationMatrix/Sig 5-->/sp124", fCheckbox309, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp141, "Lines/SpatializationMatrix/Sig 5-->/sp141", fCheckbox310, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp158, "Lines/SpatializationMatrix/Sig 5-->/sp158", fCheckbox308, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp175, "Lines/SpatializationMatrix/Sig 5-->/sp175", fCheckbox307, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__6, "Lines/SpatializationMatrix/Sig 6-->/sp  6", fCheckbox301, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_23, "Lines/SpatializationMatrix/Sig 6-->/sp 23", fCheckbox348, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_40, "Lines/SpatializationMatrix/Sig 6-->/sp 40", fCheckbox365, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_57, "Lines/SpatializationMatrix/Sig 6-->/sp 57", fCheckbox382, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_74, "Lines/SpatializationMatrix/Sig 6-->/sp 74", fCheckbox399, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_91, "Lines/SpatializationMatrix/Sig 6-->/sp 91", fCheckbox416, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp108, "Lines/SpatializationMatrix/Sig 6-->/sp108", fCheckbox433, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp125, "Lines/SpatializationMatrix/Sig 6-->/sp125", fCheckbox304, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp142, "Lines/SpatializationMatrix/Sig 6-->/sp142", fCheckbox305, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp159, "Lines/SpatializationMatrix/Sig 6-->/sp159", fCheckbox303, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp176, "Lines/SpatializationMatrix/Sig 6-->/sp176", fCheckbox302, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__7, "Lines/SpatializationMatrix/Sig 7-->/sp  7", fCheckbox296, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_24, "Lines/SpatializationMatrix/Sig 7-->/sp 24", fCheckbox349, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_41, "Lines/SpatializationMatrix/Sig 7-->/sp 41", fCheckbox366, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_58, "Lines/SpatializationMatrix/Sig 7-->/sp 58", fCheckbox383, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_75, "Lines/SpatializationMatrix/Sig 7-->/sp 75", fCheckbox400, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_92, "Lines/SpatializationMatrix/Sig 7-->/sp 92", fCheckbox417, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp109, "Lines/SpatializationMatrix/Sig 7-->/sp109", fCheckbox434, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp126, "Lines/SpatializationMatrix/Sig 7-->/sp126", fCheckbox299, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp143, "Lines/SpatializationMatrix/Sig 7-->/sp143", fCheckbox300, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp160, "Lines/SpatializationMatrix/Sig 7-->/sp160", fCheckbox298, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp177, "Lines/SpatializationMatrix/Sig 7-->/sp177", fCheckbox297, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__8, "Lines/SpatializationMatrix/Sig 8-->/sp  8", fCheckbox291, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_25, "Lines/SpatializationMatrix/Sig 8-->/sp 25", fCheckbox350, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_42, "Lines/SpatializationMatrix/Sig 8-->/sp 42", fCheckbox367, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_59, "Lines/SpatializationMatrix/Sig 8-->/sp 59", fCheckbox384, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_76, "Lines/SpatializationMatrix/Sig 8-->/sp 76", fCheckbox401, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_93, "Lines/SpatializationMatrix/Sig 8-->/sp 93", fCheckbox418, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp110, "Lines/SpatializationMatrix/Sig 8-->/sp110", fCheckbox435, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp127, "Lines/SpatializationMatrix/Sig 8-->/sp127", fCheckbox294, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp144, "Lines/SpatializationMatrix/Sig 8-->/sp144", fCheckbox295, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp161, "Lines/SpatializationMatrix/Sig 8-->/sp161", fCheckbox293, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp178, "Lines/SpatializationMatrix/Sig 8-->/sp178", fCheckbox292, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp__9, "Lines/SpatializationMatrix/Sig 9-->/sp  9", fCheckbox286, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_26, "Lines/SpatializationMatrix/Sig 9-->/sp 26", fCheckbox351, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_43, "Lines/SpatializationMatrix/Sig 9-->/sp 43", fCheckbox368, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_60, "Lines/SpatializationMatrix/Sig 9-->/sp 60", fCheckbox385, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_77, "Lines/SpatializationMatrix/Sig 9-->/sp 77", fCheckbox402, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_94, "Lines/SpatializationMatrix/Sig 9-->/sp 94", fCheckbox419, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp111, "Lines/SpatializationMatrix/Sig 9-->/sp111", fCheckbox436, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp128, "Lines/SpatializationMatrix/Sig 9-->/sp128", fCheckbox289, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp145, "Lines/SpatializationMatrix/Sig 9-->/sp145", fCheckbox290, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp162, "Lines/SpatializationMatrix/Sig 9-->/sp162", fCheckbox288, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp179, "Lines/SpatializationMatrix/Sig 9-->/sp179", fCheckbox287, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_10, "Lines/SpatializationMatrix/Sig10-->/sp 10", fCheckbox281, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_27, "Lines/SpatializationMatrix/Sig10-->/sp 27", fCheckbox352, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_44, "Lines/SpatializationMatrix/Sig10-->/sp 44", fCheckbox369, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_61, "Lines/SpatializationMatrix/Sig10-->/sp 61", fCheckbox386, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_78, "Lines/SpatializationMatrix/Sig10-->/sp 78", fCheckbox403, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_95, "Lines/SpatializationMatrix/Sig10-->/sp 95", fCheckbox420, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp112, "Lines/SpatializationMatrix/Sig10-->/sp112", fCheckbox437, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp129, "Lines/SpatializationMatrix/Sig10-->/sp129", fCheckbox284, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp146, "Lines/SpatializationMatrix/Sig10-->/sp146", fCheckbox285, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp163, "Lines/SpatializationMatrix/Sig10-->/sp163", fCheckbox283, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp180, "Lines/SpatializationMatrix/Sig10-->/sp180", fCheckbox282, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_11, "Lines/SpatializationMatrix/Sig11-->/sp 11", fCheckbox276, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_28, "Lines/SpatializationMatrix/Sig11-->/sp 28", fCheckbox353, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_45, "Lines/SpatializationMatrix/Sig11-->/sp 45", fCheckbox370, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_62, "Lines/SpatializationMatrix/Sig11-->/sp 62", fCheckbox387, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_79, "Lines/SpatializationMatrix/Sig11-->/sp 79", fCheckbox404, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_96, "Lines/SpatializationMatrix/Sig11-->/sp 96", fCheckbox421, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp113, "Lines/SpatializationMatrix/Sig11-->/sp113", fCheckbox438, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp130, "Lines/SpatializationMatrix/Sig11-->/sp130", fCheckbox279, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp147, "Lines/SpatializationMatrix/Sig11-->/sp147", fCheckbox280, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp164, "Lines/SpatializationMatrix/Sig11-->/sp164", fCheckbox278, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp181, "Lines/SpatializationMatrix/Sig11-->/sp181", fCheckbox277, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_12, "Lines/SpatializationMatrix/Sig12-->/sp 12", fCheckbox271, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_29, "Lines/SpatializationMatrix/Sig12-->/sp 29", fCheckbox354, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_46, "Lines/SpatializationMatrix/Sig12-->/sp 46", fCheckbox371, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_63, "Lines/SpatializationMatrix/Sig12-->/sp 63", fCheckbox388, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_80, "Lines/SpatializationMatrix/Sig12-->/sp 80", fCheckbox405, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_97, "Lines/SpatializationMatrix/Sig12-->/sp 97", fCheckbox422, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp114, "Lines/SpatializationMatrix/Sig12-->/sp114", fCheckbox439, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp131, "Lines/SpatializationMatrix/Sig12-->/sp131", fCheckbox274, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp148, "Lines/SpatializationMatrix/Sig12-->/sp148", fCheckbox275, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp165, "Lines/SpatializationMatrix/Sig12-->/sp165", fCheckbox273, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp182, "Lines/SpatializationMatrix/Sig12-->/sp182", fCheckbox272, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_13, "Lines/SpatializationMatrix/Sig13-->/sp 13", fCheckbox266, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_30, "Lines/SpatializationMatrix/Sig13-->/sp 30", fCheckbox355, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_47, "Lines/SpatializationMatrix/Sig13-->/sp 47", fCheckbox372, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_64, "Lines/SpatializationMatrix/Sig13-->/sp 64", fCheckbox389, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_81, "Lines/SpatializationMatrix/Sig13-->/sp 81", fCheckbox406, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_98, "Lines/SpatializationMatrix/Sig13-->/sp 98", fCheckbox423, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp115, "Lines/SpatializationMatrix/Sig13-->/sp115", fCheckbox440, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp132, "Lines/SpatializationMatrix/Sig13-->/sp132", fCheckbox269, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp149, "Lines/SpatializationMatrix/Sig13-->/sp149", fCheckbox270, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp166, "Lines/SpatializationMatrix/Sig13-->/sp166", fCheckbox268, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp183, "Lines/SpatializationMatrix/Sig13-->/sp183", fCheckbox267, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_14, "Lines/SpatializationMatrix/Sig14-->/sp 14", fCheckbox261, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_31, "Lines/SpatializationMatrix/Sig14-->/sp 31", fCheckbox356, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_48, "Lines/SpatializationMatrix/Sig14-->/sp 48", fCheckbox373, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_65, "Lines/SpatializationMatrix/Sig14-->/sp 65", fCheckbox390, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_82, "Lines/SpatializationMatrix/Sig14-->/sp 82", fCheckbox407, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_99, "Lines/SpatializationMatrix/Sig14-->/sp 99", fCheckbox424, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp116, "Lines/SpatializationMatrix/Sig14-->/sp116", fCheckbox441, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp133, "Lines/SpatializationMatrix/Sig14-->/sp133", fCheckbox264, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp150, "Lines/SpatializationMatrix/Sig14-->/sp150", fCheckbox265, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp167, "Lines/SpatializationMatrix/Sig14-->/sp167", fCheckbox263, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp184, "Lines/SpatializationMatrix/Sig14-->/sp184", fCheckbox262, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_15, "Lines/SpatializationMatrix/Sig15-->/sp 15", fCheckbox256, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_32, "Lines/SpatializationMatrix/Sig15-->/sp 32", fCheckbox357, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_49, "Lines/SpatializationMatrix/Sig15-->/sp 49", fCheckbox374, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_66, "Lines/SpatializationMatrix/Sig15-->/sp 66", fCheckbox391, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_83, "Lines/SpatializationMatrix/Sig15-->/sp 83", fCheckbox408, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp100, "Lines/SpatializationMatrix/Sig15-->/sp100", fCheckbox425, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp117, "Lines/SpatializationMatrix/Sig15-->/sp117", fCheckbox442, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp134, "Lines/SpatializationMatrix/Sig15-->/sp134", fCheckbox259, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp151, "Lines/SpatializationMatrix/Sig15-->/sp151", fCheckbox260, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp168, "Lines/SpatializationMatrix/Sig15-->/sp168", fCheckbox258, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp185, "Lines/SpatializationMatrix/Sig15-->/sp185", fCheckbox257, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_16, "Lines/SpatializationMatrix/Sig16-->/sp 16", fCheckbox331, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_33, "Lines/SpatializationMatrix/Sig16-->/sp 33", fCheckbox341, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_50, "Lines/SpatializationMatrix/Sig16-->/sp 50", fCheckbox358, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_67, "Lines/SpatializationMatrix/Sig16-->/sp 67", fCheckbox375, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp_84, "Lines/SpatializationMatrix/Sig16-->/sp 84", fCheckbox392, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp101, "Lines/SpatializationMatrix/Sig16-->/sp101", fCheckbox409, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp118, "Lines/SpatializationMatrix/Sig16-->/sp118", fCheckbox426, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp135, "Lines/SpatializationMatrix/Sig16-->/sp135", fCheckbox334, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp152, "Lines/SpatializationMatrix/Sig16-->/sp152", fCheckbox335, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp169, "Lines/SpatializationMatrix/Sig16-->/sp169", fCheckbox333, 0.0, 0.0, 1.0, 1.0) \
		p(CHECKBOX, sp186, "Lines/SpatializationMatrix/Sig16-->/sp186", fCheckbox332, 0.0, 0.0, 1.0, 1.0) \
		p(NUMENTRY, renv_freq, "RandomEnv/renv_freq", fEntry0, 10.0, 0.01, 100.0, 0.01) \
		p(HORIZONTALSLIDER, renv_short, "RandomEnv/renv_short", fHslider105, 0.5, 0.0, 1.0, 0.01) \
		p(HORIZONTALSLIDER, renv_trim, "RandomEnv/renv_trim", fHslider104, 0.0, -127.0, 18.0, 0.01) \
		p(HORIZONTALSLIDER, a_0, "a 0", fHslider103, 0.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_1, "a 1", fHslider115, 45.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_2, "a 2", fHslider116, 90.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_3, "a 3", fHslider117, 135.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_4, "a 4", fHslider118, 180.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_5, "a 5", fHslider119, 225.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_6, "a 6", fHslider120, 270.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, a_7, "a 7", fHslider121, 315.0, -360.0, 360.0, 1.0) \
		p(HORIZONTALSLIDER, phi0, "chopan/phi0", fHslider114, 30.0, 1.0, 90.0, 1.0) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

/* Faust code wrapper ------- */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "jpatcher_api.h"
#include <string.h>

#define ASSIST_INLET 	1
#define ASSIST_OUTLET 	2

#define EXTERNAL_VERSION    "0.81"
#define STR_SIZE            512

/************************** BEGIN MidiUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <cmath>

/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>


/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        std::string fNullStr = "";
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        const std::string& getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return fNullStr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
    
        const std::string& getParamAddress(FAUSTFLOAT* zone)
        {
            for (auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return fNullStr;
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            }
            if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/*************************************
 A time-stamped short MIDI message
**************************************/

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/*******************************************************************************
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 * MIDI channel is numbered in [0..15] in this layer.
 *******************************************************************************/

class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 127)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {
            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7
        };

        enum MidiCtrl {
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        };
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/*
 A class to decode NRPN and RPN messages, adapted from JUCE forum message: https://forum.juce.com/t/14bit-midi-controller-support/11517
*/

class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};


/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/

class midi_handler : public midi {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

//-------------------------------
// For timestamped MIDI messages
//-------------------------------

struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

#endif // __midi__
/**************************  END  midi.h **************************/

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/*****************************************************************************
* Helper code for MIDI meta and polyphonic 'nvoices' parsing
******************************************************************************/

struct MidiMeta : public Meta, public std::map<std::string, std::string> {
    
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
    
    static void analyse(dsp* mono_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        mono_dsp->buildUserInterface(&jsonui);
        std::string json = jsonui.JSON();
        midi_sync = ((json.find("midi") != std::string::npos) &&
                     ((json.find("start") != std::string::npos) ||
                      (json.find("stop") != std::string::npos) ||
                      (json.find("clock") != std::string::npos) ||
                      (json.find("timestamp") != std::string::npos)));
    
    #if defined(NVOICES) && NVOICES!=NUM_VOICES
        nvoices = NVOICES;
    #else
        MidiMeta meta;
        mono_dsp->metadata(&meta);
        bool found_voices = false;
        // If "options" metadata is used
        std::string options = meta.get("options", "");
        if (options != "") {
            std::map<std::string, std::string> metadata;
            std::string res;
            MetaDataUI::extractMetadata(options, res, metadata);
            if (metadata.find("nvoices") != metadata.end()) {
                nvoices = std::atoi(metadata["nvoices"].c_str());
                found_voices = true;
            }
        }
        // Otherwise test for "nvoices" metadata
        if (!found_voices) {
            std::string numVoices = meta.get("nvoices", "0");
            nvoices = std::atoi(numVoices.c_str());
        }
        nvoices = std::max<int>(0, nvoices);
    #endif
    }
    
    static bool checkPolyphony(dsp* mono_dsp)
    {
        MapUI map_ui;
        mono_dsp->buildUserInterface(&map_ui);
        bool has_freq = false;
        bool has_gate = false;
        bool has_gain = false;
        for (int i = 0; i < map_ui.getParamsCount(); i++) {
            std::string path = map_ui.getParamAddress(i);
            has_freq |= MapUI::endsWith(path, "/freq");
            has_gate |= MapUI::endsWith(path, "/gate");
            has_gain |= MapUI::endsWith(path, "/gain");
        }
        return (has_freq && has_gate && has_gain);
    }
    
};

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data is handled.
 * MIDI channel is numbered in [1..16] in this layer.
 * Channel 0 means "all channels" when receiving or sending.
 ******************************************************************************/

class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        bool inRange(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT v) { return (min <= v && v <= max); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = 0):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/*****************************************************************************
 * Base class for MIDI aware UI items
 ******************************************************************************/

class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/*****************************************************************************
 * Base class for MIDI aware UI items with timestamp support
 ******************************************************************************/

class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

//-----------
// MIDI sync
//-----------

class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->startSync(0);
            }
        }
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem {
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stopSync(0);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
};

class uiMidiClock : public uiMidiTimedItem {

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
    
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }

};

//----------------------
// Standard MIDI events
//----------------------

//---------------------------------------------
// uiMidiProgChange uses the [min...max] range
//---------------------------------------------

class uiMidiProgChange : public uiMidiTimedItem {
    
    public:
    
        FAUSTFLOAT fMin, fMax;
    
        uiMidiProgChange(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fMin(min), fMax(max)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (inRange(fMin, fMax, v)) {
                if (fChan == 0) {
                    // Send on [0..15] channels on the MIDI layer
                    for (int chan = 0; chan < 16; chan++) {
                        fMidiOut->progChange(chan, v);
                    }
                } else {
                    fMidiOut->progChange(fChan - 1, v);
                }
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiItem::modifyZone(v);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiMidiTimedItem::modifyZone(date, v);
            }
        }
        
};

class uiMidiChanPress : public uiMidiTimedItem, public uiConverter {
    
    public:
    
        uiMidiChanPress(midi* midi_out, GUI* ui,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min, FAUSTFLOAT max,
                        bool input = true,
                        MetaDataUI::Scale scale = MetaDataUI::kLin,
                        int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->chanPress(chan, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->chanPress(fChan - 1, fConverter->faust2ui(v));
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
        
};

//------------------------------------------------------
// uiMidiCtrlChange does scale (kLin/kLog/kExp) mapping
//------------------------------------------------------

class uiMidiCtrlChange : public uiMidiTimedItem, public uiConverter {
    
    private:
    
        int fCtrl;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fCtrl(ctrl)
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->ctrlChange(chan, fCtrl, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->ctrlChange(fChan - 1, fCtrl, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
};

class uiMidiPitchWheel : public uiMidiTimedItem {

    private:
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan)
        {
            if (min <= 0 && max >= 0) {
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min), 0., double(max));
            } else {
                // Degenerated case...
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min),double(min + (max - min)/FAUSTFLOAT(2)), double(max));
            }
        }
    
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->pitchWheel(chan, fConverter.faust2ui(v));
                }
            } else {
                fMidiOut->pitchWheel(fChan - 1, fConverter.faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void setRange(int val)
        {
            double semi = (val / 128) + ((val % 128) / 100.);
            fConverter.setMappingValues(0., 8191., 16383., -semi, 0., semi);
        }
 
};

//--------------------------------------------------------------
// uiMidiKeyOn does scale (kLin/kLog/kExp) mapping for velocity
//--------------------------------------------------------------

class uiMidiKeyOn : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOn;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui,
                    FAUSTFLOAT* zone,
                    FAUSTFLOAT min, FAUSTFLOAT max,
                    bool input = true,
                    MetaDataUI::Scale scale = MetaDataUI::kLin,
                    int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOn(key)
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOn, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOn, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

//---------------------------------------------------------------
// uiMidiKeyOff does scale (kLin/kLog/kExp) mapping for velocity
//---------------------------------------------------------------

class uiMidiKeyOff : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOff;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOff(key)
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOff, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOff, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

//-----------------------------------------------------------------
// uiMidiKeyPress does scale (kLin/kLog/kExp) mapping for velocity
//-----------------------------------------------------------------

class uiMidiKeyPress : public uiMidiTimedItem, public uiConverter {

    private:
    
        int fKey;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui,
                       FAUSTFLOAT* zone,
                       FAUSTFLOAT min, FAUSTFLOAT max,
                       bool input = true,
                       MetaDataUI::Scale scale = MetaDataUI::kLin,
                       int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKey(key)
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKey, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKey, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi, public MetaDataUI {

    // Add uiItem subclasses objects are deallocated by the inherited GUI class
    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::vector<uiMidiProgChange*>                  TProgChangeTable;
    typedef std::vector<uiMidiChanPress*>                   TChanPressTable;
    typedef std::map <int, std::vector<uiMidiKeyOn*> >      TKeyOnTable;
    typedef std::map <int, std::vector<uiMidiKeyOff*> >     TKeyOffTable;
    typedef std::map <int, std::vector<uiMidiKeyPress*> >   TKeyPressTable;
    typedef std::vector<uiMidiPitchWheel*>                  TPitchWheelTable;
    
    protected:
    
        TCtrlChangeTable fCtrlChangeTable;
        TProgChangeTable fProgChangeTable;
        TChanPressTable  fChanPressTable;
        TKeyOnTable      fKeyOnTable;
        TKeyOffTable     fKeyOffTable;
        TKeyOnTable      fKeyTable;
        TKeyPressTable   fKeyPressTable;
        TPitchWheelTable fPitchWheelTable;
        
        std::vector<uiMidiStart*> fStartTable;
        std::vector<uiMidiStop*>  fStopTable;
        std::vector<uiMidiClock*> fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    unsigned chan;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u %u", &num, &chan) == 2) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &chan) == 1) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input, chan));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "pgm") == 0) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &chan) == 1) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone), chan));
                        } else if ((fMetaAux[i].second == "chanpress")) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone)));
                        } else if ((gsscanf(fMetaAux[i].second.c_str(), "pitchwheel %u", &chan) == 1) || (gsscanf(fMetaAux[i].second.c_str(), "pitchbend %u", &chan) == 1)) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input, chan));
                        } else if ((fMetaAux[i].second == "pitchwheel") || (fMetaAux[i].second == "pitchbend")) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
                        // MIDI sync
                        } else if (fMetaAux[i].second == "start") {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "stop") {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "clock") {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        // Explicit metadata to activate 'timestamp' mode
                        } else if (fMetaAux[i].second == "timestamp") {
                            fTimeStamp = true;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }
    
        template <typename TABLE>
        void updateTable1(TABLE& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                // channel_aux == 0 means "all channels"
                if (channel_aux == 0 || channel == channel_aux - 1) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename TABLE>
        void updateTable2(TABLE& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    // channel_aux == 0 means "all channels"
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        if (fTimeStamp) {
                            table[val1][i]->modifyZone(date, FAUSTFLOAT(val2));
                        } else {
                            table[val1][i]->modifyZone(FAUSTFLOAT(val2));
                        }
                    }
                }
            }
        }
    
    public:
    
        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            fDelete = delete_handler;
            fTimeStamp = false;
        }
 
        virtual ~MidiUI() 
        { 
            fMidiHandler->removeMidiIn(this);
            if (fDelete) delete fMidiHandler;
        }
    
        bool run() { return fMidiHandler->startMidi(); }
        void stop() { fMidiHandler->stopMidi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            MetaDataUI::declare(zone, key, val);
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API
    
        void key(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyTable, date, channel, note, velocity);
        }
    
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyOnTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOn
            key(date, channel, note, velocity);
            return nullptr;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOffTable>(fKeyOffTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            key(date, channel, note, 0);
        }
        
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            updateTable2<TCtrlChangeTable>(fCtrlChangeTable, date, channel, ctrl, value);
        }
    
        void rpn(double date, int channel, int ctrl, int value)
        {
            if (ctrl == midi::PITCH_BEND_RANGE) {
                for (size_t i = 0; i < fPitchWheelTable.size(); i++) {
                    // channel_aux == 0 means "all channels"
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable1<TProgChangeTable>(fProgChangeTable, date, channel, pgm);
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            updateTable1<TPitchWheelTable>(fPitchWheelTable, date, channel, wheel);
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            updateTable2<TKeyPressTable>(fKeyPressTable, date, channel, pitch, press);
        }
        
        void chanPress(double date, int channel, int press)
        {
            updateTable1<TChanPressTable>(fChanPressTable, date, channel, press);
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (size_t i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (size_t i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (size_t i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/**************************  END  MidiUI.h **************************/
/************************** BEGIN mspUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
//
//  mspUI.h for static Max/MSP externals and faustgen~
//
//  Created by Martin Di Rollo on 18/04/12.
//  Copyright (c) 2012-2019 Grame. All rights reserved.
//

#ifndef _mspUI_h
#define _mspUI_h

#include <math.h>
#include <string>
#include <map>


#define STR_SIZE    512
#define MULTI_SIZE  256

#ifdef WIN32
#include <stdio.h>
#define snprintf _snprintf
#ifndef NAN
    static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif
#endif

using namespace std;

struct Max_Meta1 : Meta
{
    int fCount;
    
    Max_Meta1():fCount(0)
    {}
    
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            fCount++;
        }
    }
};

struct Max_Meta2 : Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};

struct Max_Meta3 : Meta
{
    string fName;
    
    bool endWith(const string& str, const string& suffix)
    {
        size_t i = str.rfind(suffix);
        return (i != string::npos) && (i == (str.length() - suffix.length()));
    }
    
    void declare(const char* key, const char* value)
    {
        if ((strcmp("filename", key) == 0)) {
            string val = value;
            if (endWith(value, ".dsp")) {
                fName = "com.grame." + val.substr(0, val.size() - 4) + "~";
            } else {
                fName = "com.grame." + val + "~";
            }
        }
    }
};

class mspUIObject {
    
    protected:
        
        string fLabel;
        FAUSTFLOAT* fZone;
        
        FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}
        
    public:
        
        mspUIObject(const string& label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
        virtual ~mspUIObject() {}
        
        virtual void setValue(FAUSTFLOAT f) { *fZone = range(0.0, 1.0, f); }
        virtual FAUSTFLOAT getValue() { return *fZone; }
    
        virtual FAUSTFLOAT getInitValue() { return FAUSTFLOAT(0); }
        virtual FAUSTFLOAT getMinValue() { return FAUSTFLOAT(0); }
        virtual FAUSTFLOAT getMaxValue() { return FAUSTFLOAT(0); }
    
        virtual void toString(char* buffer) {}
        virtual string getName() { return fLabel; }
};

class mspCheckButton : public mspUIObject {
    
    public:
        
        mspCheckButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspCheckButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, STR_SIZE, "CheckButton(float): %s", fLabel.c_str());
        }
};

class mspButton : public mspUIObject {
    
    public:
        
        mspButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, STR_SIZE, "Button(float): %s", fLabel.c_str());
        }
};

class mspSlider : public mspUIObject {
    
    private:
        
        FAUSTFLOAT fInit;
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fStep;
        
    public:
        
        mspSlider(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        :mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
        virtual ~mspSlider() {}
        
        void toString(char* buffer)
        {
            stringstream str;
            str << "Slider(float): " << fLabel << " [init=" << fInit << ":min=" << fMin << ":max=" << fMax << ":step=" << fStep << ":cur=" << *fZone << "]";
            string res = str.str();
            snprintf(buffer, STR_SIZE, "%s", res.c_str());
        }
        
        void setValue(FAUSTFLOAT f) { *fZone = range(fMin, fMax, f); }
    
        virtual FAUSTFLOAT getInitValue() { return fInit; }
        virtual FAUSTFLOAT getMinValue() { return fMin; }
        virtual FAUSTFLOAT getMaxValue() { return fMax; }
    
};

class mspBargraph : public mspUIObject {
    
    private:
        
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fCurrent;
        
    public:
        
        mspBargraph(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        :mspUIObject(label,zone), fMin(min), fMax(max), fCurrent(*zone) {}
        virtual ~mspBargraph() {}
        
        void toString(char* buffer)
        {
            stringstream str;
            str << "Bargraph(float): " << fLabel << " [min=" << fMin << ":max=" << fMax << ":cur=" << *fZone << "]";
            string res = str.str();
            snprintf(buffer, STR_SIZE, "%s", res.c_str());
        }
    
        // special version
        virtual FAUSTFLOAT getValue(bool& new_val)
        {
            if (*fZone != fCurrent) {
                fCurrent = *fZone;
                new_val = true;
            } else {
                new_val = false;
            }
            return fCurrent;
        }
    
        virtual FAUSTFLOAT getMinValue() { return fMin; }
        virtual FAUSTFLOAT getMaxValue() { return fMax; }
    
};

class mspUI : public UI, public PathBuilder
{
    private:
        
        map<string, mspUIObject*> fInputLabelTable;      // Input table using labels
        map<string, mspUIObject*> fInputPathTable;       // Input table using paths
        map<string, mspUIObject*> fOutputLabelTable;     // Table containing bargraph with labels
        map<string, mspUIObject*> fOutputPathTable;      // Table containing bargraph with paths
        
        map<const char*, const char*> fDeclareTable;
        
        FAUSTFLOAT* fMultiTable[MULTI_SIZE];
        int fMultiIndex;
        int fMultiControl;
        
        string createLabel(const char* label)
        {
            map<const char*, const char*>::reverse_iterator it;
            if (fDeclareTable.size() > 0) {
                unsigned int i = 0;
                string res = string(label);
                char sep = '[';
                for (it = fDeclareTable.rbegin(); it != fDeclareTable.rend(); it++, i++) {
                    res = res + sep + (*it).first + ":" + (*it).second;
                    sep = ',';
                }
                res += ']';
                fDeclareTable.clear();
                return res;
            } else {
                return string(label);
            }
        }
    
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fInputLabelTable[string(label)] = obj;
            fInputPathTable[buildPath(label)] = obj;
            fDeclareTable.clear();
        }
    
        void addBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            mspUIObject* obj = new mspBargraph(createLabel(label), zone, min, max);
            fOutputLabelTable[string(label)] = obj;
            fOutputPathTable[buildPath(label)] = obj;
            fDeclareTable.clear();
        }
    
    public:
        
        typedef map<string, mspUIObject*>::iterator iterator;
        
        mspUI()
        {
            for (int i = 0; i < MULTI_SIZE; i++) {
                fMultiTable[i] = 0;
            }
            fMultiIndex = fMultiControl = 0;
        }
    
        virtual ~mspUI()
        {
            clear();
        }
        
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            mspUIObject* obj = new mspButton(createLabel(label), zone);
            fInputLabelTable[string(label)] = obj;
            fInputPathTable[buildPath(label)] = obj;
        }
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            mspUIObject* obj = new mspCheckButton(createLabel(label), zone);
            fInputLabelTable[string(label)] = obj;
            fInputPathTable[buildPath(label)] = obj;
        }
        
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
    
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addBargraph(label, zone, min, max);
        }
    
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addBargraph(label, zone, min, max);
        }
        
        void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        void openTabBox(const char* label) { pushLabel(label); fDeclareTable.clear(); }
        void openHorizontalBox(const char* label) { pushLabel(label); fDeclareTable.clear(); }
        void openVerticalBox(const char* label) { pushLabel(label); fDeclareTable.clear(); }
        void closeBox() { popLabel(); fDeclareTable.clear(); }
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "multi") == 0) {
                int index = atoi(val);
                if (index >= 0 && index < MULTI_SIZE) {
                    fMultiTable[index] = zone;
                    fMultiControl++;
                } else {
                    post("Invalid multi index = %d", index);
                }
            }
            
            fDeclareTable[key] = val;
        }
        
        void setMultiValues(FAUSTFLOAT* multi, int buffer_size)
        {
            for (int read = 0; read < buffer_size; read++) {
                int write = (fMultiIndex + read) & (MULTI_SIZE - 1);
                if (fMultiTable[write]) {
                    *fMultiTable[write] = multi[read];
                }
            }
            fMultiIndex += buffer_size;
        }
        
        bool isMulti() { return fMultiControl > 0; }
        
        bool isValue(const string& name)
        {
            return (fInputLabelTable.count(name) || fInputPathTable.count(name));
        }
    
        bool isOutputValue(const string& name)
        {
            return fOutputPathTable.count(name);
        }
    
        bool isInputValue(const string& name)
        {
            return fInputPathTable.count(name);
        }
    
        bool setValue(const string& name, FAUSTFLOAT val)
        {
            if (fInputLabelTable.count(name)) {
                fInputLabelTable[name]->setValue(val);
                return true;
            } else if (fInputPathTable.count(name)) {
                fInputPathTable[name]->setValue(val);
                return true;
            } else {
                return false;
            }
        }
    
        FAUSTFLOAT getOutputValue(const string& name, bool& new_val)
        {
            return static_cast<mspBargraph*>(fOutputPathTable[name])->getValue(new_val);
        }
        
        iterator begin1() { return fInputLabelTable.begin(); }
        iterator end1() { return fInputLabelTable.end(); }
        
        iterator begin2() { return fInputPathTable.begin(); }
        iterator end2() { return fInputPathTable.end(); }
    
        iterator begin3() { return fOutputLabelTable.begin(); }
        iterator end3() { return fOutputLabelTable.end(); }
    
        iterator begin4() { return fOutputPathTable.begin(); }
        iterator end4() { return fOutputPathTable.end(); }
    
        int inputItemsCount() { return fInputLabelTable.size(); }
        int outputItemsCount() { return fOutputLabelTable.size(); }
    
        void clear()
        {
            for (auto& it : fInputLabelTable) {
                delete it.second;
            }
            fInputLabelTable.clear();
            fInputPathTable.clear();
            
            for (auto& it : fOutputLabelTable) {
                delete it.second;
            }
            fOutputLabelTable.clear();
            fOutputPathTable.clear();
        }
        
        void displayControls()
        {
            post("------- Range and path ----------");
            for (auto& it : fInputPathTable) {
                char param[STR_SIZE];
                it.second->toString(param);
                post(param);
                string path = "Complete path: " + it.first;
                post(path.c_str());
            }
            post("---------------------------------");
        }
    
        static bool checkDigit(const string& name)
        {
            for (int i = name.size() - 1; i >= 0; i--) {
                if (isdigit(name[i])) { return true; }
            }
            return false;
        }
        
        static int countDigit(const string& name)
        {
            int count = 0;
            for (int i = name.size() - 1; i >= 0; i--) {
                if (isdigit(name[i])) { count++; }
            }
            return count;
        }

};

//==============
// MIDI handler
//==============

struct faustgen_midi : public midi_handler {
    
    void* m_midi_outlet = NULL;
    
    faustgen_midi(void* midi_outlet = NULL):m_midi_outlet(midi_outlet)
    {}
    
    void sendMessage(std::vector<unsigned char>& message)
    {
        assert(m_midi_outlet);
        for (int i = 0; i < message.size(); i++) {
            outlet_int(m_midi_outlet, message[i]);
        }
    }
    
    // MIDI output API
    MapUI* keyOn(int channel, int pitch, int velocity)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_NOTE_ON + channel);
        message.push_back(pitch);
        message.push_back(velocity);
        sendMessage(message);
        return NULL;
    }
    
    void keyOff(int channel, int pitch, int velocity)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_NOTE_OFF + channel);
        message.push_back(pitch);
        message.push_back(velocity);
        sendMessage(message);
    }
    
    void ctrlChange(int channel, int ctrl, int val)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_CONTROL_CHANGE + channel);
        message.push_back(ctrl);
        message.push_back(val);
        sendMessage(message);
    }
    
    void chanPress(int channel, int press)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_AFTERTOUCH + channel);
        message.push_back(press);
        sendMessage(message);
    }
    
    void progChange(int channel, int pgm)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_PROGRAM_CHANGE + channel);
        message.push_back(pgm);
        sendMessage(message);
    }
    
    void keyPress(int channel, int pitch, int press)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_POLY_AFTERTOUCH + channel);
        message.push_back(pitch);
        message.push_back(press);
        sendMessage(message);
    }
    
    void pitchWheel(int channel, int wheel)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_PITCH_BEND + channel);
        message.push_back(wheel & 0x7F);           // lsb 7bit
        message.push_back((wheel >> 7) & 0x7F);    // msb 7bit
        sendMessage(message);
    }
    
    void ctrlChange14bits(int channel, int ctrl, int value) {}
    
    void startSync(double date)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_START);
        sendMessage(message);
    }
    
    void stopSync(double date)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_STOP);
        sendMessage(message);
    }
    
    void clock(double date)
    {
        std::vector<unsigned char> message;
        message.push_back(MIDI_CLOCK);
        sendMessage(message);
    }
    
    void sysEx(double, std::vector<unsigned char>& message)
    {
        sendMessage(message);
    }
};

#endif
/**************************  END  mspUI.h **************************/
/************************** BEGIN poly-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <float.h>
#include <assert.h>

/************************** BEGIN proxy-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>

/************************** BEGIN JSONUIDecoder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <functional>

/************************** BEGIN CGlue.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef CGLUE_H
#define CGLUE_H

/************************** BEGIN CInterface.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
struct Soundfile;

/*******************************************************************************
 * UI, Meta and MemoryManager structures for C code.
 ******************************************************************************/

// -- widget's layouts

typedef void (* openTabBoxFun) (void* ui_interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* ui_interface, const char* label);
typedef void (* openVerticalBoxFun) (void* ui_interface, const char* label);
typedef void (* closeBoxFun) (void* ui_interface);

// -- active widgets

typedef void (* addButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive widgets

typedef void (* addHorizontalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

// -- soundfiles
    
typedef void (* addSoundfileFun) (void* ui_interface, const char* label, const char* url, struct Soundfile** sf_zone);

typedef void (* declareFun) (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    addSoundfileFun addSoundfile;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (void* ui_interface, const char* key, const char* value);

typedef struct {

    void* metaInterface;
    
    metaDeclareFun declare;

} MetaGlue;

/***************************************
 *  Interface for the DSP object
 ***************************************/

typedef char dsp_imp;
    
typedef dsp_imp* (* newDspFun) ();
typedef void (* destroyDspFun) (dsp_imp* dsp);
typedef int (* getNumInputsFun) (dsp_imp* dsp);
typedef int (* getNumOutputsFun) (dsp_imp* dsp);
typedef void (* buildUserInterfaceFun) (dsp_imp* dsp, UIGlue* ui);
typedef int (* getSampleRateFun) (dsp_imp* dsp);
typedef void (* initFun) (dsp_imp* dsp, int sample_rate);
typedef void (* classInitFun) (int sample_rate);
typedef void (* instanceInitFun) (dsp_imp* dsp, int sample_rate);
typedef void (* instanceConstantsFun) (dsp_imp* dsp, int sample_rate);
typedef void (* instanceResetUserInterfaceFun) (dsp_imp* dsp);
typedef void (* instanceClearFun) (dsp_imp* dsp);
typedef void (* computeFun) (dsp_imp* dsp, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
typedef void (* metadataFun) (MetaGlue* meta);
    
/***************************************
 * DSP memory manager functions
 ***************************************/

typedef void* (* allocateFun) (void* manager_interface, size_t size);
typedef void (* destroyFun) (void* manager_interface, void* ptr);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} MemoryManagerGlue;

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CInterface.h **************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * UI glue code
 ******************************************************************************/
 
class UIFloat
{

    public:

        UIFloat() {}

        virtual ~UIFloat() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, float* zone) = 0;
        virtual void addCheckButton(const char* label, float* zone) = 0;
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(float* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueFloat(void* cpp_interface)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueFloat(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueFloat(void* cpp_interface, float* zone, const char* key, const char* value)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

class UIDouble
{

    public:

        UIDouble() {}

        virtual ~UIDouble() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, double* zone) = 0;
        virtual void addCheckButton(const char* label, double* zone) = 0;
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max) = 0;
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(double* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueDouble(void* cpp_interface)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueDouble(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueDouble(void* cpp_interface, double* zone, const char* key, const char* value)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

static void buildUIGlue(UIGlue* glue, UI* ui_interface, bool is_double)
{
    glue->uiInterface = ui_interface;
    
    if (is_double) {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueDouble);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueDouble);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueDouble);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueDouble);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueDouble);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueDouble);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueDouble);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueDouble);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueDouble);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueDouble);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueDouble);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueDouble);
        glue->declare = reinterpret_cast<declareFun>(declareGlueDouble);
    } else {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueFloat);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueFloat);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueFloat);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueFloat);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueFloat);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueFloat);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueFloat);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueFloat);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueFloat);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueFloat);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueFloat);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueFloat);
        glue->declare = reinterpret_cast<declareFun>(declareGlueFloat);
    }
}
    
class UITemplate
{
    
    private:
        
        void* fCPPInterface;
        
    public:
        
        UITemplate(void* cpp_interface):fCPPInterface(cpp_interface)
        {}
        
        virtual ~UITemplate() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)
        {
            openTabBoxGlueFloat(fCPPInterface, label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            openHorizontalBoxGlueFloat(fCPPInterface, label);
        }
        virtual void openVerticalBox(const char* label)
        {
            openVerticalBoxGlueFloat(fCPPInterface, label);
        }
        virtual void closeBox()
        {
            closeBoxGlueFloat(fCPPInterface);
        }
        
        // float version
        
        // -- active widgets
        
        virtual void addButton(const char* label, float* zone)
        {
            addButtonGlueFloat(fCPPInterface, label, zone);
        }
        virtual void addCheckButton(const char* label, float* zone)
        {
            addCheckButtonGlueFloat(fCPPInterface, label, zone);
        }
        
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
        {
            addVerticalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
        {
            addHorizontalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
        {
            addNumEntryGlueFloat(fCPPInterface, label, zone, init, min, max, step);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
        {
            addHorizontalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
        }
        
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
        {
            addVerticalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
        }
    
        // -- metadata declarations
        
        virtual void declare(float* zone, const char* key, const char* val)
        {
            declareGlueFloat(fCPPInterface, zone, key, val);
        }
        
        // double version
        
        virtual void addButton(const char* label, double* zone)
        {
            addButtonGlueDouble(fCPPInterface, label, zone);
        }
        virtual void addCheckButton(const char* label, double* zone)
        {
            addCheckButtonGlueDouble(fCPPInterface, label, zone);
        }
        
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
        {
            addVerticalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
        {
            addHorizontalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
        {
            addNumEntryGlueDouble(fCPPInterface, label, zone, init, min, max, step);
        }
    
        // -- soundfiles
        
        virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
        {
            addSoundfileGlueFloat(fCPPInterface, label, url, sf_zone);
        }
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max)
        {
            addHorizontalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
        }
        
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max)
        {
            addVerticalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
        }
    
        // -- metadata declarations
        
        virtual void declare(double* zone, const char* key, const char* val)
        {
            declareGlueDouble(fCPPInterface, zone, key, val);
        }

};

/*******************************************************************************
 * Meta glue code
 ******************************************************************************/

static void declareMetaGlue(void* cpp_interface, const char* key, const char* value)
{
    Meta* meta_interface = static_cast<Meta*>(cpp_interface);
    meta_interface->declare(key, value);
}

static void buildMetaGlue(MetaGlue* glue, Meta* meta)
{
    glue->metaInterface = meta;
    glue->declare = declareMetaGlue;
}
    
/*******************************************************************************
 * Memory manager glue code
 ******************************************************************************/

static void* allocateMemoryManagerGlue(void* cpp_interface, size_t size)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    return manager_interface->allocate(size);
}
    
static void destroyMemoryManagerGlue(void* cpp_interface, void* ptr)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    manager_interface->destroy(ptr);
}

static void buildManagerGlue(MemoryManagerGlue* glue, dsp_memory_manager* manager)
{
    glue->managerInterface = manager;
    glue->allocate = allocateMemoryManagerGlue;
    glue->destroy = destroyMemoryManagerGlue;
}

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CGlue.h **************************/

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//-------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface'
//-------------------------------------------------------------------

#define REAL_UI(ui_interface) reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(offset)      reinterpret_cast<REAL*>(&memory_block[offset])
#define REAL_EXT_ADR(offset)  reinterpret_cast<FAUSTFLOAT*>(&memory_block[offset])
#define SOUNDFILE_ADR(offset) reinterpret_cast<Soundfile**>(&memory_block[offset])

typedef std::function<void(double)> ReflectFunction;
typedef std::function<double()> ModifyFunction;

struct ExtZoneParam {

    virtual void reflectZone() = 0;
    virtual void modifyZone() = 0;
    
    virtual void setReflectZoneFun(ReflectFunction reflect) = 0;
    virtual void setModifyZoneFun(ModifyFunction modify) = 0;
    
    virtual ~ExtZoneParam()
    {}
    
};

template <typename REAL>
struct JSONUIDecoderReal {
    
    struct ZoneParam : public ExtZoneParam {
        
        REAL fZone;
        int fIndex;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(int index, ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fIndex(index), fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(int index, ReflectFunction reflect = [](REAL value) {}, ModifyFunction modify = []() { return REAL(-1); })
        :fIndex(index), fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { fReflect(fZone); }
        void modifyZone() { fZone = fModify(); }
    #endif
        
        void setReflectZoneFun(ReflectFunction reflect) { fReflect = reflect; }
        void setModifyZoneFun(ModifyFunction modify) { fModify = modify; }
        
    };

    typedef std::vector<ExtZoneParam*> controlMap;
  
    std::string fName;
    std::string fFileName;
    std::string fJSON;
    std::string fVersion;
    std::string fCompileOptions;
    
    std::map<std::string, std::string> fMetadata;
    std::vector<itemInfo> fUiItems;
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    Soundfile** fSoundfiles;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fSoundfileItems;
    int fDSPSize;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]

    bool isInput(const std::string& type)
    {
        return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox");
    }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }
    
    std::string getString(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? map[key].first : "";
    }
    
    int getInt(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? int(map[key].second) : -1;
    }
    
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        fPathInputTable[index]->setReflectZoneFun(fun);
    }
    
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        fPathOutputTable[index]->setModifyZoneFun(fun);
    }

    JSONUIDecoderReal(const std::string& json)
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::pair<std::string, double> > meta_data1;
        std::map<std::string, std::vector<std::string> > meta_data2;
        parseJson(p, meta_data1, fMetadata, meta_data2, fUiItems);
        
        // meta_data1 contains <name : val>, <inputs : val>, <ouputs : val> pairs etc...
        fName = getString(meta_data1, "name");
        fFileName = getString(meta_data1, "filename");
        fVersion = getString(meta_data1, "version");
        fCompileOptions = getString(meta_data1, "compile_options");
        
        if (meta_data2.find("library_list") != meta_data2.end()) {
            fLibraryList = meta_data2["library_list"];
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = getInt(meta_data1, "size");
        fNumInputs = getInt(meta_data1, "inputs");
        fNumOutputs = getInt(meta_data1, "outputs");
        fSRIndex = getInt(meta_data1, "sr_index");
       
        fSoundfileItems = 0;
        for (auto& it : fUiItems) {
            std::string type = it.type;
            if (isSoundfile(type)) {
                fSoundfileItems++;
            }
        }
        
        fSoundfiles = new Soundfile*[fSoundfileItems];
        
        // Prepare the fPathTable and init zone
        for (auto& it : fUiItems) {
            std::string type = it.type;
            // Meta data declaration for input items
            if (isInput(type)) {
                ZoneParam* param = new ZoneParam(it.index);
                fPathInputTable.push_back(param);
                param->fZone = it.init;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                ZoneParam* param = new ZoneParam(it.index);
                fPathOutputTable.push_back(param);
                param->fZone = REAL(0);
            }
        }
    }
    
    virtual ~JSONUIDecoderReal()
    {
        delete [] fSoundfiles;
        for (auto& it : fPathInputTable) {
            delete it;
        }
        for (auto& it : fPathOutputTable) {
            delete it;
        }
    }
    
    void metadata(Meta* m)
    {
        for (auto& it : fMetadata) {
            m->declare(it.first.c_str(), it.second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        for (auto& it : fMetadata) {
            m->declare(m->metaInterface, it.first.c_str(), it.second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        int item = 0;
        for (auto& it : fUiItems) {
            if (isInput(it.type)) {
                static_cast<ZoneParam*>(fPathInputTable[item++])->fZone = it.init;
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        for (auto& it : fUiItems) {
            int offset = it.index;
            if (isInput(it.type)) {
                *REAL_ADR(offset) = it.init;
            } else if (isSoundfile(it.type)) {
                if (*SOUNDFILE_ADR(offset) == nullptr) {
                    *SOUNDFILE_ADR(offset) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
   
    void buildUserInterface(UI* ui_interface)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        int countIn = 0;
        int countOut = 0;
        int countSound = 0;
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") { 
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), &fSoundfiles[countSound]);
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
            
            if (isInput(type)) {
                countIn++;
            } else if (isOutput(type)) {
                countOut++;
            } else if (isSoundfile(type)) {
                countSound++;
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            int offset = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), REAL_ADR(offset));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(offset));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), REAL_ADR(offset));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            int offset = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, 0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset));
            } else if (type == "soundfile") {
                ui_interface->addSoundfile(ui_interface->uiInterface, it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(offset));
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset));
            } else if (type == "close") {
                ui_interface->closeBox(ui_interface->uiInterface);
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) return true;
        }
        return false;
    }
    
};

// Templated decoder

struct JSONUITemplatedDecoder
{

    virtual ~JSONUITemplatedDecoder()
    {}
    
    virtual void metadata(Meta* m) = 0;
    virtual void metadata(MetaGlue* glue) = 0;
    virtual int getDSPSize() = 0;
    virtual std::string getName() = 0;
    virtual std::string getLibVersion() = 0;
    virtual std::string getCompileOptions() = 0;
    virtual std::vector<std::string> getLibraryList() = 0;
    virtual std::vector<std::string> getIncludePathnames() = 0;
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual int getSampleRate(char* memory_block) = 0;
    virtual void setReflectZoneFun(int index, ReflectFunction fun) = 0;
    virtual void setModifyZoneFun(int index, ModifyFunction fun) = 0;
    virtual std::vector<ExtZoneParam*>& getInputControls() = 0;
    virtual std::vector<ExtZoneParam*>& getOutputControls() = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

// Float templated decoder

struct JSONUIFloatDecoder : public JSONUIDecoderReal<float>, public JSONUITemplatedDecoder
{
    JSONUIFloatDecoder(const std::string& json):JSONUIDecoderReal<float>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderReal<float>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderReal<float>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block)  { return JSONUIDecoderReal<float>::getSampleRate(memory_block); }
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        JSONUIDecoderReal<float>::setReflectZoneFun(index, fun);
    }
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        JSONUIDecoderReal<float>::setModifyZoneFun(index, fun);
    }
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderReal<float>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface)
    {
        JSONUIDecoderReal<float>::buildUserInterface(ui_interface);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<float>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<float>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderReal<float>::hasCompileOption(option); }
};

// Double templated decoder

struct JSONUIDoubleDecoder : public JSONUIDecoderReal<double>, public JSONUITemplatedDecoder
{
    JSONUIDoubleDecoder(const std::string& json):JSONUIDecoderReal<double>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderReal<double>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderReal<double>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block) { return JSONUIDecoderReal<double>::getSampleRate(memory_block); }
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        JSONUIDecoderReal<double>::setReflectZoneFun(index, fun);
    }
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        JSONUIDecoderReal<double>::setModifyZoneFun(index, fun);
    }
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderReal<double>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface)
    {
        JSONUIDecoderReal<double>::buildUserInterface(ui_interface);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<double>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<double>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderReal<double>::hasCompileOption(option); }
};

// FAUSTFLOAT templated decoder

struct JSONUIDecoder : public JSONUIDecoderReal<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderReal<FAUSTFLOAT>(json)
    {}
};

// Generic factory

static JSONUITemplatedDecoder* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDoubleDecoder(json);
    } else {
        return new JSONUIFloatDecoder(json);
    }
}

#endif
/**************************  END  JSONUIDecoder.h **************************/

//----------------------------------------------------------------
//  Proxy dsp definition created from the DSP JSON description
//  This class allows a 'proxy' dsp to control a real dsp 
//  possibly running somewhere else.
//----------------------------------------------------------------

class proxy_dsp : public dsp {

    private:
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
        }
          
        proxy_dsp(dsp* dsp)
        {
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            fSampleRate = dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
       
        virtual int getNumInputs() { return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy dsp 
        virtual void init(int sample_rate)
        {
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int sample_rate) { fSampleRate = sample_rate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif
/**************************  END  proxy-dsp.h **************************/
/************************** BEGIN JSONControl.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JSON_CONTROL__
#define __JSON_CONTROL__

#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct JSONControl {
    
    virtual std::string getJSON() { return ""; }

    virtual void setParamValue(const std::string& path, FAUSTFLOAT value) {}

    virtual FAUSTFLOAT getParamValue(const std::string& path) { return 0; }
    
    virtual ~JSONControl()
    {}
    
};

#endif
/**************************  END  JSONControl.h **************************/

#define kActiveVoice      0
#define kFreeVoice        -1
#define kReleaseVoice     -2
#define kNoVoice          -3

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

/**
 * Allows to control zones in a grouped manner.
 */

class GroupUI : public GUI, public PathBuilder
{

    private:

        std::map<std::string, uiGroupItem*> fLabelZoneMap;

        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            if (!MapUI::endsWith(label, "/gate")
                && !MapUI::endsWith(label, "/freq")
                && !MapUI::endsWith(label, "/key")
                && !MapUI::endsWith(label, "/gain")
                && !MapUI::endsWith(label, "/vel")
                && !MapUI::endsWith(label, "/velocity")) {

                // Groups all controllers except 'freq/key', 'gate', and 'gain/vel|velocity'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }

        uiCallbackItem* fPanic;

    public:

        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        }
    
        virtual ~GroupUI()
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        }

        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }

        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }

        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }

};

/**
 * One voice of polyphony.
 */

struct dsp_voice : public MapUI, public decorator_dsp {
    
    typedef std::function<double(int)> TransformFunction;
  
    static double midiToFreq(double note)
    {
        return 440.0 * std::pow(2.0, (note-69.0)/12.0);
    }

    int fNote;                          // Playing note actual pitch
    int fDate;                          // KeyOn date
    int fRelease;                       // Current number of samples used in release mode to detect end of note
    int fMaxRelease;                    // Max of samples used in release mode to detect end of note
    FAUSTFLOAT fLevel;                  // Last audio block level
    std::vector<std::string> fGatePath; // Paths of 'gate' control
    std::vector<std::string> fGainPath; // Paths of 'gain/vel|velocity' control
    std::vector<std::string> fFreqPath; // Paths of 'freq/key' control
    TransformFunction        fKeyFun;   // MIDI key to freq conversion function
    TransformFunction        fVelFun;   // MIDI velocity to gain conversion function
 
    dsp_voice(dsp* dsp):decorator_dsp(dsp)
    {
        // Default versions
        fVelFun = [](int velocity) { return double(velocity)/127.0; };
        fKeyFun = [](int pitch) { return midiToFreq(pitch); };
        dsp->buildUserInterface(this);
        fNote = kFreeVoice;
        fLevel = FAUSTFLOAT(0);
        fDate = 0;
        fRelease = 0;
        fMaxRelease = dsp->getSampleRate()/2; // One 1/2 sec used in release mode to detect end of note
        extractPaths(fGatePath, fFreqPath, fGainPath);
    }
    virtual ~dsp_voice()
    {}

    void extractPaths(std::vector<std::string>& gate, std::vector<std::string>& freq, std::vector<std::string>& gain)
    {
        // Keep gain/vel|velocity, freq/key and gate labels
        for (auto& it : getMap()) {
            std::string path = it.first;
            if (endsWith(path, "/gate")) {
                gate.push_back(path);
            } else if (endsWith(path, "/freq")) {
                fKeyFun = [](int pitch) { return midiToFreq(pitch); };
                freq.push_back(path);
            } else if (endsWith(path, "/key")) {
                fKeyFun = [](int pitch) { return pitch; };
                freq.push_back(path);
            } else if (endsWith(path, "/gain")) {
                fVelFun = [](int velocity) { return double(velocity)/127.0; };
                gain.push_back(path);
            } else if (endsWith(path, "/vel") || endsWith(path, "/velocity")) {
                fVelFun = [](int velocity) { return double(velocity); };
                gain.push_back(path);
            }
        }
    }
   
    // MIDI velocity [0..127]
    void keyOn(int pitch, int velocity)
    {
        keyOn(pitch, fVelFun(velocity));
    }

    // Normalized MIDI velocity [0..1]
    void keyOn(int pitch, double velocity)
    {
        // So that DSP state is always re-initialized
        fDSP->instanceClear();
        
        for (size_t i = 0; i < fFreqPath.size(); i++) {
            setParamValue(fFreqPath[i], fKeyFun(pitch));
        }
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(1));
        }
        for (size_t i = 0; i < fGainPath.size(); i++) {
            setParamValue(fGainPath[i], velocity);
        }
        
        fNote = pitch;
    }

    void keyOff(bool hard = false)
    {
        // No use of velocity for now...
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        if (hard) {
            // Immediately stop voice
            fNote = kFreeVoice;
        } else {
            // Release voice
            fRelease = fMaxRelease;
            fNote = kReleaseVoice;
        }
    }

};

/**
 * A group of voices.
 */

struct dsp_voice_group {

    GroupUI fGroups;

    std::vector<dsp_voice*> fVoiceTable; // Individual voices
    dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control

    FAUSTFLOAT fPanic;

    bool fVoiceControl;
    bool fGroupControl;

    dsp_voice_group(uiCallback cb, void* arg, bool control, bool group)
        :fGroups(&fPanic, cb, arg),
        fVoiceGroup(0), fPanic(FAUSTFLOAT(0)),
        fVoiceControl(control), fGroupControl(group)
    {}

    virtual ~dsp_voice_group()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            delete fVoiceTable[i];
        }
        delete fVoiceGroup;
    }

    void addVoice(dsp_voice* voice)
    {
        fVoiceTable.push_back(voice);
    }

    void clearVoices()
    {
        fVoiceTable.clear();
    }

    void init()
    {
        // Groups all uiItem for a given path
        fVoiceGroup = new proxy_dsp(fVoiceTable[0]);
        fVoiceGroup->buildUserInterface(&fGroups);
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->buildUserInterface(&fGroups);
        }
    }
    
    void instanceResetUserInterface()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->instanceResetUserInterface();
        }
    }

    void buildUserInterface(UI* ui_interface)
    {
        if (fVoiceTable.size() > 1) {
            ui_interface->openTabBox("Polyphonic");

            // Grouped voices UI
            ui_interface->openVerticalBox("Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();

            // If not grouped, also add individual voices UI
            if (!fGroupControl) {
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    char buffer[32];
                    snprintf(buffer, 32, ((fVoiceTable.size() < 8) ? "Voice%ld" : "V%ld"), long(i+1));
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }

            ui_interface->closeBox();
        } else {
            fVoiceTable[0]->buildUserInterface(ui_interface);
        }
    }

};

/**
 * Base class for MIDI controllable DSP.
 */

#ifdef EMCC
#endif

class dsp_poly : public decorator_dsp, public midi, public JSONControl {

    protected:
    
    #ifdef EMCC
        MapUI fMapUI;
        std::string fJSON;
        midi_handler fMIDIHandler;
        MidiUI fMIDIUI;
    #endif
    
    public:
    
    #ifdef EMCC
        dsp_poly(dsp* dsp):decorator_dsp(dsp), fMIDIUI(&fMIDIHandler)
        {
            JSONUI jsonui(getNumInputs(), getNumOutputs());
            buildUserInterface(&jsonui);
            fJSON = jsonui.JSON(true);
            buildUserInterface(&fMapUI);
            buildUserInterface(&fMIDIUI);
        }
    #else
        dsp_poly(dsp* dsp):decorator_dsp(dsp)
        {}
    #endif
    
        virtual ~dsp_poly() {}
    
        // Reimplemented for EMCC
    #ifdef EMCC
        virtual int getNumInputs() { return decorator_dsp::getNumInputs(); }
        virtual int getNumOutputs() { return decorator_dsp::getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { decorator_dsp::buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return decorator_dsp::getSampleRate(); }
        virtual void init(int sample_rate) { decorator_dsp::init(sample_rate); }
        virtual void instanceInit(int sample_rate) { decorator_dsp::instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { decorator_dsp::instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { decorator_dsp::instanceResetUserInterface(); }
        virtual void instanceClear() { decorator_dsp::instanceClear(); }
        virtual dsp_poly* clone() { return new dsp_poly(fDSP->clone()); }
        virtual void metadata(Meta* m) { decorator_dsp::metadata(m); }
    
        // Additional API
        std::string getJSON()
        {
            return fJSON;
        }
    
        virtual void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            fMapUI.setParamValue(path, value);
            GUI::updateAllGuis();
        }
        
        virtual FAUSTFLOAT getParamValue(const std::string& path) { return fMapUI.getParamValue(path); }

        virtual void computeJS(int count, uintptr_t inputs, uintptr_t outputs)
        {
            decorator_dsp::compute(count, reinterpret_cast<FAUSTFLOAT**>(inputs),reinterpret_cast<FAUSTFLOAT**>(outputs));
        }
    #endif
    
        virtual MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return midi::keyOn(channel, pitch, velocity);
        }
        virtual void keyOff(int channel, int pitch, int velocity)
        {
            midi::keyOff(channel, pitch, velocity);
        }
        virtual void keyPress(int channel, int pitch, int press)
        {
            midi::keyPress(channel, pitch, press);
        }
        virtual void chanPress(int channel, int press)
        {
            midi::chanPress(channel, press);
        }
        virtual void ctrlChange(int channel, int ctrl, int value)
        {
            midi::ctrlChange(channel, ctrl, value);
        }
        virtual void ctrlChange14bits(int channel, int ctrl, int value)
        {
            midi::ctrlChange14bits(channel, ctrl, value);
        }
        virtual void pitchWheel(int channel, int wheel)
        {
        #ifdef EMCC
            fMIDIUI.pitchWheel(0., channel, wheel);
            GUI::updateAllGuis();
        #else
            midi::pitchWheel(channel, wheel);
        #endif
        }
        virtual void progChange(int channel, int pgm)
        {
            midi::progChange(channel, pgm);
        }
    
        // Group API
        virtual void setGroup(bool group) {}
        virtual bool getGroup() { return false; }

};

/**
 * Polyphonic DSP: groups a set of DSP to be played together or triggered by MIDI.
 *
 * All voices are preallocated by cloning the single DSP voice given at creation time.
 * Dynamic voice allocation is done in 'getFreeVoice'
 */

class FilDeSoi1PanStereo_poly : public dsp_voice_group, public dsp_poly {

    private:

        FAUSTFLOAT** fMixBuffer;
        FAUSTFLOAT** fOutBuffer;
        int fDate;
  
        FAUSTFLOAT mixCheckVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            FAUSTFLOAT level = 0;
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    level = std::max<FAUSTFLOAT>(level, (FAUSTFLOAT)fabs(mixChannel[frame]));
                    outChannel[frame] += mixChannel[frame];
                }
            }
            return level;
        }
    
        void mixVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    outChannel[frame] += mixChannel[frame];
                }
            }
        }
    
        void copy(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memcpy(outBuffer[chan], mixBuffer[chan], count * sizeof(FAUSTFLOAT));
            }
        }

        void clear(int count, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memset(outBuffer[chan], 0, count * sizeof(FAUSTFLOAT));
            }
        }
    
        int getPlayingVoice(int pitch)
        {
            int voice_playing = kNoVoice;
            int oldest_date_playing = INT_MAX;
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fNote == pitch) {
                    // Keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
            
            return voice_playing;
        }
    
        // Always returns a voice
        int getFreeVoice()
        {
            int voice = kNoVoice;
            
            // Looks for the first available voice
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fNote == kFreeVoice) {
                    voice = int(i);
                    goto result;
                }
            }

            {
                // Otherwise steal one
                int voice_release = kNoVoice;
                int voice_playing = kNoVoice;
                
                int oldest_date_release = INT_MAX;
                int oldest_date_playing = INT_MAX;

                // Scan all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    if (fVoiceTable[i]->fNote == kReleaseVoice) {
                        // Keeps oldest release voice
                        if (fVoiceTable[i]->fDate < oldest_date_release) {
                            oldest_date_release = fVoiceTable[i]->fDate;
                            voice_release = int(i);
                        }
                    } else {
                        // Otherwise keeps oldest playing voice
                        if (fVoiceTable[i]->fDate < oldest_date_playing) {
                            oldest_date_playing = fVoiceTable[i]->fDate;
                            voice_playing = int(i);
                        }
                    }
                }
            
                // Then decide which one to steal
                if (oldest_date_release != INT_MAX) {
                    std::cout << "Steal release voice : voice_date " << fVoiceTable[voice_release]->fDate;
                    std::cout << " cur_date = " << fDate << " voice = " << voice_release << std::endl;
                    voice = voice_release;
                    goto result;
                } else if (oldest_date_playing != INT_MAX) {
                    std::cout << "Steal playing voice : voice_date " << fVoiceTable[voice_playing]->fDate;
                    std::cout << " cur_date = " << fDate << " voice = " << voice_playing << std::endl;
                    voice = voice_playing;
                    goto result;
                } else {
                    assert(false);
                    return kNoVoice;
                }
            }
            
        result:
            fVoiceTable[voice]->fDate = fDate++;
            fVoiceTable[voice]->fNote = kActiveVoice;
            return voice;
        }

        static void panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<FilDeSoi1PanStereo_poly*>(arg)->allNotesOff(true);
            }
        }

        bool checkPolyphony()
        {
            if (fVoiceTable.size() > 0) {
                return true;
            } else {
                std::cout << "DSP is not polyphonic...\n";
                return false;
            }
        }

    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be used for one voice. Beware: FilDeSoi1PanStereo_poly will use and finally delete the pointer.
         * @param nvoices - number of polyphony voices, should be at least 1
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
         *                If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *                setGroup/getGroup methods can be used to set/get the group state.
         *
         */
        FilDeSoi1PanStereo_poly(dsp* dsp,
                   int nvoices,
                   bool control = false,
                   bool group = true)
        : dsp_voice_group(panic, this, control, group), dsp_poly(dsp) // dsp parameter is deallocated by ~dsp_poly
        {
            fDate = 0;

            // Create voices
            assert(nvoices > 0);
            for (int i = 0; i < nvoices; i++) {
                addVoice(new dsp_voice(dsp->clone()));
            }

            // Init audio output buffers
            fMixBuffer = new FAUSTFLOAT*[getNumOutputs()];
            fOutBuffer = new FAUSTFLOAT*[getNumOutputs()];
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                fMixBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
                fOutBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }

            dsp_voice_group::init();
        }

        virtual ~FilDeSoi1PanStereo_poly()
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                delete[] fMixBuffer[chan];
                delete[] fOutBuffer[chan];
            }
            delete[] fMixBuffer;
            delete[] fOutBuffer;
        }

        // DSP API
    
        void buildUserInterface(UI* ui_interface)
        {
            dsp_voice_group::buildUserInterface(ui_interface);
        }

        void init(int sample_rate)
        {
            decorator_dsp::init(sample_rate);
            fVoiceGroup->init(sample_rate);
            fPanic = FAUSTFLOAT(0);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate)
        {
            decorator_dsp::instanceConstants(sample_rate);
            fVoiceGroup->instanceConstants(sample_rate);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceConstants(sample_rate);
            }
        }

        void instanceResetUserInterface()
        {
            decorator_dsp::instanceResetUserInterface();
            fVoiceGroup->instanceResetUserInterface();
            fPanic = FAUSTFLOAT(0);
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceResetUserInterface();
            }
        }

        void instanceClear()
        {
            decorator_dsp::instanceClear();
            fVoiceGroup->instanceClear();
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceClear();
            }
        }

        virtual FilDeSoi1PanStereo_poly* clone()
        {
            return new FilDeSoi1PanStereo_poly(fDSP->clone(), int(fVoiceTable.size()), fVoiceControl, fGroupControl);
        }

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= MIX_BUFFER_SIZE);

            // First clear the intermediate fOutBuffer
            clear(count, fOutBuffer);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fNote != kFreeVoice) {
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                        // Check the level to possibly set the voice in kFreeVoice again
                        voice->fRelease -= count;
                        if ((voice->fNote == kReleaseVoice)
                            && (voice->fRelease < 0)
                            && (voice->fLevel < VOICE_STOP_LEVEL)) {
                            voice->fNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, fOutBuffer);
                }
            }
            
            // Finally copy intermediate buffer to outputs
            copy(count, fOutBuffer, outputs);
        }

        void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        // Terminate all active voices, gently or immediately (depending of 'hard' value)
        void allNotesOff(bool hard = false)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->keyOff(hard);
            }
        }

        // Additional polyphonic API
        MapUI* newVoice()
        {
            int voice = getFreeVoice();
            // So that DSP state is always re-initialized
            fVoiceTable[voice]->instanceClear();
            return fVoiceTable[voice];
        }

        void deleteVoice(MapUI* voice)
        {
            std::vector<dsp_voice*>::iterator it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                (*it)->keyOff();
            } else {
                std::cout << "Voice not found\n";
            }
        }
    
        // Group API
        void setGroup(bool group) { fGroupControl = group; }
        bool getGroup() { return fGroupControl; }

        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getFreeVoice();
                fVoiceTable[voice]->keyOn(pitch, velocity);
                return fVoiceTable[voice];
            } else {
                return 0;
            }
        }

        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getPlayingVoice(pitch);
                if (voice != kNoVoice) {
                    fVoiceTable[voice]->keyOff();
                } else {
                    std::cout << "Playing pitch = " << pitch << " not found\n";
                }
            }
        }

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

};

/**
 * Polyphonic DSP with an integrated effect. fPolyDSP will respond to MIDI messages.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
        
        dsp_poly* fPolyDSP;
        
    public:
        
        dsp_poly_effect(dsp_poly* dsp1, dsp* dsp2)
        :dsp_poly(dsp2), fPolyDSP(dsp1)
        {}
        
        virtual ~dsp_poly_effect()
        {
            // dsp_poly_effect is also a decorator_dsp, which will free fPolyDSP
        }
        
        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return fPolyDSP->keyOn(channel, pitch, velocity);
        }
        void keyOff(int channel, int pitch, int velocity)
        {
            fPolyDSP->keyOff(channel, pitch, velocity);
        }
        void keyPress(int channel, int pitch, int press)
        {
            fPolyDSP->keyPress(channel, pitch, press);
        }
        void chanPress(int channel, int press)
        {
            fPolyDSP->chanPress(channel, press);
        }
        void ctrlChange(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange(channel, ctrl, value);
        }
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange14bits(channel, ctrl, value);
        }
        void pitchWheel(int channel, int wheel)
        {
            fPolyDSP->pitchWheel(channel, wheel);
        }
        void progChange(int channel, int pgm)
        {
            fPolyDSP->progChange(channel, pgm);
        }
        
        // Group API
        void setGroup(bool group)
        {
            fPolyDSP->setGroup(group);
        }
        bool getGroup()
        {
            return fPolyDSP->getGroup();
        }
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */

struct dsp_poly_factory : public dsp_factory {
    
    dsp_factory* fProcessFactory;
    dsp_factory* fEffectFactory;
    
    std::string getEffectCode(const std::string& dsp_content)
    {
        std::stringstream effect_code;
        effect_code << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        effect_code << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        effect_code << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        return effect_code.str();
    }

    dsp_poly_factory(dsp_factory* process_factory = NULL,
                     dsp_factory* effect_factory = NULL):
    fProcessFactory(process_factory)
    ,fEffectFactory(effect_factory)
    {}
    
    virtual ~dsp_poly_factory()
    {}
    
    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    virtual std::string getCompileOptions() { return fProcessFactory->getCompileOptions(); }
    virtual std::vector<std::string> getLibraryList() { return fProcessFactory->getLibraryList(); }
    virtual std::vector<std::string> getIncludePathnames() { return fProcessFactory->getIncludePathnames(); }
    
    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }
    
    /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete'
     *
     * @param nvoices - number of polyphony voices, should be at least 1
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group)
    {
        dsp_poly* dsp_poly = new FilDeSoi1PanStereo_poly(fProcessFactory->createDSPInstance(), nvoices, control, group);
        if (fEffectFactory) {
            // the 'dsp_poly' object has to be controlled with MIDI, so kept separated from new dsp_sequencer(...) object
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, fEffectFactory->createDSPInstance()));
        } else {
            return new dsp_poly_effect(dsp_poly, dsp_poly);
        }
    }
    
    /* Create a new DSP instance, to be deleted with C++ 'delete' */
    dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }
    
};

#endif // __poly_dsp__
/**************************  END  poly-dsp.h **************************/

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static t_class* faust_class;

/*--------------------------------------------------------------------------*/
static const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

/*--------------------------------------------------------------------------*/
typedef struct faust
{
    t_pxobject m_ob;
    t_atom *m_seen, *m_want;
    map<string, vector<t_object*> > m_output_table;
    short m_where;
    bool m_mute;
    void** m_args;
    mspUI* m_dspUI;
    dsp* m_dsp;
    FilDeSoi1PanStereo_poly* m_dsp_poly;
    void* m_control_outlet;
    char* m_json;
    t_systhread_mutex m_mutex;    
    int m_Inputs;
    int m_Outputs;
    SaveUI* m_savedUI;
#ifdef MIDICTRL
    MidiUI* m_midiUI;
    faustgen_midi* m_midiHandler;
    void* m_midi_outlet;
#endif
#ifdef SOUNDFILE
    SoundUI* m_soundInterface;
#endif
#ifdef OSCCTRL
    OSCUI* m_oscInterface;
#endif
} t_faust;

void faust_create_jsui(t_faust* x);
void faust_make_json(t_faust* x);

/*--------------------------------------------------------------------------*/
void faust_allocate(t_faust* x, int nvoices)
{
    // Delete old
    delete x->m_dsp;
    x->m_dspUI->clear();
    
    if (nvoices > 0) {
    #ifdef POST
        post("polyphonic DSP voices = %d", nvoices);
    #endif
        x->m_dsp_poly = new FilDeSoi1PanStereo_poly(new FilDeSoi1PanStereo(), nvoices, true, true);
    #ifdef POLY2
        x->m_dsp = new dsp_sequencer(x->m_dsp_poly, new effect());
    #else
        x->m_dsp = x->m_dsp_poly;
    #endif
    #ifdef MIDICTRL
        x->m_midiHandler->addMidiIn(x->m_dsp_poly);
    #endif
    } else {
    #ifdef POST
        post("monophonic DSP");
    #endif
        // Create a DS/US + Filter adapted DSP
        x->m_dsp = createSRAdapter<FAUSTFLOAT>(new FilDeSoi1PanStereo(), DOWN_SAMPLING, UP_SAMPLING, FILTER_TYPE);
    }
    
#ifdef MIDICTRL
    x->m_dsp->buildUserInterface(x->m_midiUI);
#endif
  
    // Possible sample adaptation
    if (sizeof(FAUSTFLOAT) == 4) {
        x->m_dsp = new dsp_sample_adapter<FAUSTFLOAT, double>(x->m_dsp);
    }
}

/*--------------------------------------------------------------------------*/
void faust_anything(t_faust* obj, t_symbol* s, short ac, t_atom* av)
{
    bool res = false;
    string name = string((s)->s_name);
    
    // If no argument is there, consider it as a toggle message for a button
    if (ac == 0 && obj->m_dspUI->isValue(name)) {
        
        FAUSTFLOAT off = FAUSTFLOAT(0.0);
        FAUSTFLOAT on = FAUSTFLOAT(1.0);
        obj->m_dspUI->setValue(name, off);
        obj->m_dspUI->setValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        faust_anything(obj, s, 1, av);
        
    } else if (mspUI::checkDigit(name)) { // List of values
        
        int pos, ndigit = 0;
        for (pos = name.size() - 1; pos >= 0; pos--) {
            if (isdigit(name[pos]) || name[pos] == ' ') {
                ndigit++;
            } else {
                break;
            }
        }
        pos++;
        
        string prefix = name.substr(0, pos);
        string num_base = name.substr(pos);
        int num = atoi(num_base.c_str());
        
        int i;
        t_atom* ap;
       
        // Increment ap each time to get to the next atom
        for (i = 0, ap = av; i < ac; i++, ap++) {
            FAUSTFLOAT value;
            switch (atom_gettype(ap)) {
                case A_LONG:
                    value = FAUSTFLOAT(ap[0].a_w.w_long);
                    break;
                case A_FLOAT:
                    value = FAUSTFLOAT(ap[0].a_w.w_float);
                    break;
                default:
                    post("Invalid argument in parameter setting"); 
                    return;         
            }
            
            string num_val = to_string(num + i);
            stringstream param_name; param_name << prefix;
            for (int i = 0; i < ndigit - mspUI::countDigit(num_val); i++) {
                param_name << ' ';
            }
            param_name << num_val;
              
            // Try special naming scheme for list of parameters
            res = obj->m_dspUI->setValue(param_name.str(), value);
            
            // Otherwise try standard name
            if (!res) {
                res = obj->m_dspUI->setValue(name, value);
            }
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        }
        
    } else {
        // Standard parameter name
        FAUSTFLOAT value = (av[0].a_type == A_LONG) ? FAUSTFLOAT(av[0].a_w.w_long) : FAUSTFLOAT(av[0].a_w.w_float);
        res = obj->m_dspUI->setValue(name, value);
        if (!res) {
            post("Unknown parameter : %s", (s)->s_name);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_polyphony(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    if (systhread_mutex_lock(x->m_mutex) == MAX_ERR_NONE) {
        
    #ifdef MIDICTRL
        if (x->m_dsp_poly) {
            x->m_midiHandler->removeMidiIn(x->m_dsp_poly);
        }
    #endif
        
        faust_allocate(x, av[0].a_w.w_long);
        
        // Initialize at the system's sampling rate
        x->m_dsp->init(long(sys_getsr()));
        // Initialize User Interface (here connnection with controls)
        x->m_dsp->buildUserInterface(x->m_dspUI);
        
        // Prepare JSON
        faust_make_json(x);
        
        // Send JSON to JS script
        faust_create_jsui(x);
        
        // Load old controller state
        x->m_dsp->buildUserInterface(x->m_savedUI);
        
        systhread_mutex_unlock(x->m_mutex);
    } else {
        post("Mutex lock cannot be taken...");
    }
}

/*--------------------------------------------------------------------------*/
#ifdef MIDICTRL
void faust_midievent(t_faust* x, t_symbol* s, short ac, t_atom* av) 
{
    if (ac > 0) {
        int type = (int)av[0].a_w.w_long & 0xf0;
        int channel = (int)av[0].a_w.w_long & 0x0f;
                
        if (ac == 1) {
            x->m_midiHandler->handleSync(0.0, av[0].a_w.w_long);
        } else if (ac == 2) {
            x->m_midiHandler->handleData1(0.0, type, channel, av[1].a_w.w_long);
        } else if (ac == 3) {
            x->m_midiHandler->handleData2(0.0, type, channel, av[1].a_w.w_long, av[2].a_w.w_long);
        }
    }
}
#endif

/*--------------------------------------------------------------------------*/
void faust_create_jsui(t_faust* x)
{
    t_object *patcher, *box, *obj;
    object_obex_lookup((t_object*)x, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        // Notify JSON
        if (obj && strcmp(object_classname(obj)->s_name, "js") == 0) {
            t_atom json;
            atom_setsym(&json, gensym(x->m_json));
            object_method_typed(obj, gensym("anything"), 1, &json, 0);
        }
    }
        
    // Keep all outputs to be notified in update_outputs
    x->m_output_table.clear();
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        t_symbol* scriptingname = jbox_get_varname(obj); // scripting name
        // Keep control outputs
        if (scriptingname && x->m_dspUI->isOutputValue(scriptingname->s_name)) {
            x->m_output_table[scriptingname->s_name].push_back(obj);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_update_outputs(t_faust* x)
{
    for (auto& it1 : x->m_output_table) {
        bool new_val = false;
        FAUSTFLOAT value = x->m_dspUI->getOutputValue(it1.first, new_val);
        if (new_val) {
            t_atom at_value;
            atom_setfloat(&at_value, value);
            for (auto& it2 : it1.second) {
                object_method_typed(it2, gensym("float"), 1, &at_value, 0);
            }
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_make_json(t_faust* x)
{
    // Prepare JSON
    if (x->m_json) free(x->m_json);
    JSONUI builder(x->m_dsp->getNumInputs(), x->m_dsp->getNumOutputs());
    x->m_dsp->metadata(&builder);
    x->m_dsp->buildUserInterface(&builder);
    x->m_json = strdup(builder.JSON().c_str());
}

/*--------------------------------------------------------------------------*/
void* faust_new(t_symbol* s, short ac, t_atom* av)
{
    bool midi_sync = false;
    int nvoices = 0;
    
    FilDeSoi1PanStereo* tmp_dsp = new FilDeSoi1PanStereo();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
    t_faust* x = (t_faust*)object_alloc(faust_class);
    
    x->m_savedUI = new SaveLabelUI();
    x->m_dspUI = NULL;
    x->m_dsp = NULL;
    x->m_dsp_poly = NULL;
    x->m_json = NULL;
    x->m_mute = false;
    
#ifdef MIDICTRL
    x->m_midi_outlet = outlet_new((t_pxobject*)x, NULL);
    x->m_midiHandler = new faustgen_midi(x->m_midi_outlet);
    x->m_midiUI = new MidiUI(x->m_midiHandler);
#endif
    
    x->m_dspUI = new mspUI();
    
    faust_allocate(x, nvoices);
    
    x->m_Inputs = x->m_dsp->getNumInputs();
    x->m_Outputs = x->m_dsp->getNumOutputs();
    
    x->m_control_outlet = outlet_new((t_pxobject*)x, (char*)"list");
 
    // Initialize at the system's sampling rate
    x->m_dsp->init(long(sys_getsr()));
    // Initialize User Interface (here connnection with controls)
    x->m_dsp->buildUserInterface(x->m_dspUI);
    
    t_max_err err = systhread_mutex_new(&x->m_mutex, SYSTHREAD_MUTEX_NORMAL);
    if (err != MAX_ERR_NONE) {
        post("Cannot allocate mutex...");
    }
    
    // Prepare JSON
    faust_make_json(x);
    
    int num_input;
    if (x->m_dspUI->isMulti()) {
        num_input = x->m_dsp->getNumInputs() + 1;
    } else {
        num_input = x->m_dsp->getNumInputs();
    }
    
    x->m_args = (void**)calloc((num_input + x->m_dsp->getNumOutputs()) + 2, sizeof(void*));
    /* Multi in */
    dsp_setup((t_pxobject*)x, num_input);

    /* Multi out */
    for (int i = 0; i < x->m_dsp->getNumOutputs(); i++) {
        outlet_new((t_pxobject*)x, (char*)"signal");
    }

    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different

#ifdef SOUNDFILE
    Max_Meta3 meta3;
    x->m_dsp->metadata(&meta3);
    string bundle_path_str = SoundUI::getBinaryPathFrom(meta3.fName);
    if (bundle_path_str == "") {
        post("Bundle_path '%s' cannot be found!", meta3.fName.c_str());
    }
    x->m_soundInterface = new SoundUI(bundle_path_str);
    // SoundUI has to be dispatched on all internal voices
    if (x->m_dsp_poly) x->m_dsp_poly->setGroup(false);
    x->m_dsp->buildUserInterface(x->m_soundInterface);
    if (x->m_dsp_poly) x->m_dsp_poly->setGroup(true);
#endif
    
#ifdef OSCCTRL
    x->m_oscInterface = NULL;
#endif
    
    // Send JSON to JS script
    faust_create_jsui(x);
    
    // Load old controller state
    x->m_dsp->buildUserInterface(x->m_savedUI);
    
    // Display controls
#ifdef POST
    x->m_dspUI->displayControls();
#endif   
    // Get attributes values
    attr_args_process(x, ac, av);
    
    return x;
}

#ifdef OSCCTRL
// osc 'IP inport outport xmit bundle'
/*--------------------------------------------------------------------------*/
void faust_osc(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    if (ac == 5) {
        if (systhread_mutex_lock(x->m_mutex) == MAX_ERR_NONE) {
            
            delete x->m_oscInterface;
            
            const char* argv1[32];
            int argc1 = 0;
            
            argv1[argc1++] = "Faust";
            
            argv1[argc1++]  = "-desthost";
            argv1[argc1++]  = atom_getsym(&av[0])->s_name;
            
            char inport[32];
            snprintf(inport, 32, "%ld", long(av[1].a_w.w_long));
            argv1[argc1++] = "-port";
            argv1[argc1++] = inport;
            
            char outport[32];
            snprintf(outport, 32, "%ld", long(av[2].a_w.w_long));
            argv1[argc1++] = "-outport";
            argv1[argc1++] = outport;
            
            char xmit[32];
            snprintf(xmit, 32, "%ld", long(av[3].a_w.w_long));
            argv1[argc1++] = "-xmit";
            argv1[argc1++] = xmit;
            
            char bundle[32];
            snprintf(bundle, 32, "%ld", long(av[4].a_w.w_long));
            argv1[argc1++] = "-bundle";
            argv1[argc1++] = bundle;
            
            x->m_oscInterface = new OSCUI("Faust", argc1, (char**)argv1);
            x->m_dsp->buildUserInterface(x->m_oscInterface);
            x->m_oscInterface->run();

            post(x->m_oscInterface->getInfos().c_str());

            systhread_mutex_unlock(x->m_mutex);
        } else {
            post("Mutex lock cannot be taken...");
        }
    } else {
        post("Should be : osc 'IP inport outport xmit(0|1|2) bundle(0|1)'");
    }
}
#endif

/*--------------------------------------------------------------------------*/
// Reset controllers to init value and send [path, init, min, max]
void faust_init(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    // Reset internal state
    x->m_savedUI->reset();
    
    // Input controllers
    for (mspUI::iterator it = x->m_dspUI->begin2(); it != x->m_dspUI->end2(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());    // init value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
    // Output controllers
    for (mspUI::iterator it = x->m_dspUI->begin4(); it != x->m_dspUI->end4(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());    // init value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
 }

/*--------------------------------------------------------------------------*/
void faust_dump_inputs(t_faust* x)
{
    // Input controllers
    for (mspUI::iterator it = x->m_dspUI->begin2(); it != x->m_dspUI->end2(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());    // cur value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
}

/*--------------------------------------------------------------------------*/
void faust_dump_outputs(t_faust* x)
{
    // Output controllers
    for (mspUI::iterator it = x->m_dspUI->begin4(); it != x->m_dspUI->end4(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());    // cur value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
}

/*--------------------------------------------------------------------------*/
// Dump controllers as list of [path, cur, min, max]
void faust_dump(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    faust_dump_inputs(x);
    faust_dump_outputs(x);
}

/*--------------------------------------------------------------------------*/
void faust_dblclick(t_faust* x, long inlet)
{
    x->m_dspUI->displayControls();
}

/*--------------------------------------------------------------------------*/
//11/13/2015 : faust_assist is actually called at each click in the patcher, so we now use 'faust_dblclick' to display the parameters...
void faust_assist(t_faust* x, void* b, long msg, long a, char* dst)
{
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->m_dsp->getNumInputs() == 0) {
                sprintf(dst, "(message) : Unused Input");
            } else {
                sprintf(dst, "(signal) : Audio Input %ld", (a+1));
            }
        } else if (a < x->m_dsp->getNumInputs()) {
            sprintf(dst, "(signal) : Audio Input %ld", (a+1));
        }
    } else if (msg == ASSIST_OUTLET) {
        if (a < x->m_dsp->getNumOutputs()) {
            sprintf(dst, "(signal) : Audio Output %ld", (a+1));
        } else {
            sprintf(dst, "(list) : [path, cur|init, min, max]*");
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_mute(t_faust* obj, t_symbol* s, short ac, t_atom* at)
{
    if (atom_gettype(at) == A_LONG) {
        obj->m_mute = atom_getlong(at);
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust* x)
{
    dsp_free((t_pxobject*)x);
    delete x->m_dsp;
    delete x->m_dspUI;
    delete x->m_savedUI;
    if (x->m_args) free(x->m_args);
    if (x->m_json) free(x->m_json);
    systhread_mutex_free(x->m_mutex);
#ifdef MIDICTRL
    // m_midiUI *must* be deleted before m_midiHandler
    delete x->m_midiUI;
    delete x->m_midiHandler;
#endif
#ifdef SOUNDFILE
    delete x->m_soundInterface;
#endif
#ifdef OSCCTRL
    delete x->m_oscInterface;
#endif
}

/*--------------------------------------------------------------------------*/
void faust_perform64(t_faust* x, t_object* dsp64, double** ins, long numins, double** outs, long numouts, long sampleframes, long flags, void* userparam)
{
    AVOIDDENORMALS;
    if (!x->m_mute && systhread_mutex_trylock(x->m_mutex) == MAX_ERR_NONE) {
        if (x->m_dsp) {
            if (x->m_dspUI->isMulti()) {
                x->m_dspUI->setMultiValues(reinterpret_cast<FAUSTFLOAT*>(ins[0]), sampleframes);
                x->m_dsp->compute(sampleframes, reinterpret_cast<FAUSTFLOAT**>(++ins), reinterpret_cast<FAUSTFLOAT**>(outs));
            } else {
                x->m_dsp->compute(sampleframes, reinterpret_cast<FAUSTFLOAT**>(ins), reinterpret_cast<FAUSTFLOAT**>(outs));
            }
        #ifdef OSCCTRL
            if (x->m_oscInterface) x->m_oscInterface->endBundle();
        #endif
            //faust_update_outputs(x);
            // Use the right outlet to output messages
            faust_dump_outputs(x);
        }
    #if defined(MIDICTRL) || defined(OSCCTRL)
        GUI::updateAllGuis();
    #endif
        systhread_mutex_unlock(x->m_mutex);
    } else {
        // Write null buffers to outs
        for (int i = 0; i < numouts; i++) {
             memset(outs[i], 0, sizeof(double) * sampleframes);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_dsp64(t_faust* x, t_object* dsp64, short* count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, faust_perform64, 0, NULL);
}

/*--------------------------------------------------------------------------*/
t_max_err faust_attr_set(t_faust* x, t_object* attr, long ac, t_atom* av)
{
    if (ac && av) {
        t_symbol* attrname = (t_symbol*)object_method(attr, gensym("getname"));
        // Redirect on the generic message handling method
        faust_anything(x, attrname, ac, av);
    }
    return MAX_ERR_NONE;
}

/*--------------------------------------------------------------------------*/
#ifdef _WIN32
extern "C" int main(void)
#else
void ext_main(void* r)
#endif
{
    string file_name = string(FAUST_FILE_NAME);
    // Remove ".dsp" ending
    string class_name = file_name.erase(file_name.size()-4) + "~";
    t_class* c = class_new(class_name.c_str(), (method)faust_new, (method)faust_free, sizeof(t_faust), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)faust_anything, "anything", A_GIMME, 0);
    class_addmethod(c, (method)faust_polyphony, "polyphony", A_GIMME, 0);
#ifdef OSCCTRL
    class_addmethod(c, (method)faust_osc, "osc", A_GIMME, 0);
#endif
    class_addmethod(c, (method)faust_init, "init", A_GIMME, 0);
    class_addmethod(c, (method)faust_dump, "dump", A_GIMME, 0);
#ifdef MIDICTRL
    class_addmethod(c, (method)faust_midievent, "midievent", A_GIMME, 0);
#endif
    class_addmethod(c, (method)faust_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)faust_dblclick, "dblclick", A_CANT, 0);
    class_addmethod(c, (method)faust_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)faust_mute, "mute", A_GIMME, 0);
    
    dsp* tmp_dsp = new FilDeSoi1PanStereo();
    mspUI tmp_UI;
    tmp_dsp->buildUserInterface(&tmp_UI);
    
    // Setup attributes
    if (sizeof(FAUSTFLOAT) == 4) {
        for (mspUI::iterator it = tmp_UI.begin1(); it != tmp_UI.end1(); it++) {
            CLASS_ATTR_FLOAT(c, (*it).first.c_str(), 0, t_faust, m_ob);
            CLASS_ATTR_ACCESSORS(c, (*it).first.c_str(), NULL, (method)faust_attr_set);
        }
    } else {
        for (mspUI::iterator it = tmp_UI.begin1(); it != tmp_UI.end1(); it++) {
            CLASS_ATTR_DOUBLE(c, (*it).first.c_str(), 0, t_faust, m_ob);
            CLASS_ATTR_ACCESSORS(c, (*it).first.c_str(), NULL, (method)faust_attr_set);
        }
    }
    
    class_dspinit(c);
    class_register(CLASS_BOX, c);
    faust_class = c;
#ifdef POST
    post((char*)"Faust DSP object v%s (sample = %s bits code = %s)", EXTERNAL_VERSION, ((sizeof(FAUSTFLOAT) == 4) ? "32" : "64"), getCodeSize());
    post((char*)"Copyright (c) 2012-2021 Grame");
#endif
    Max_Meta1 meta1;
    tmp_dsp->metadata(&meta1);
    if (meta1.fCount > 0) {
    #ifdef POST
        Max_Meta2 meta2;
        post("------------------------------");
        tmp_dsp->metadata(&meta2);
        post("------------------------------");
    #endif
    }
    delete(tmp_dsp);
#ifdef _WIN32
    return 0;
#endif
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/


#endif
