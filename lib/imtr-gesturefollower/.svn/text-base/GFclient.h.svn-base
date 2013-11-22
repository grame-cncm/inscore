/*
 *  GFclient.h
 *  gf
 *
 *  Created by Bruno Zamborlin on 28/06/10.
 *
 */

#ifndef   GFCLIENT
#define   GFCLIENT


/***********************			GFClient CLASS		********************/

class GFClient {
public:
  virtual void warning(const std::string description) = 0;
  virtual void memoryError(const std::string description) = 0;
  virtual void phraseOutOfBounds(const std::string invokedMethod, const int wrongPhraseIndex) = 0;
  virtual void errorGeneric(const std::string description) = 0;
  virtual void sceneEnded() = 0;
  virtual void alphaIsZero(int phraseIndex) = 0;
};

#endif
