#include "bbwb.h"

namespace tarski {


  vector<string> BBWBComm::options = {"verbose"};

  virtual TAndRef preProcess(std::vector<SRef> &args, optionsHandler& o) {
      int N = args.size();
      if (N < 1) {throw TarskiException("bbwb requires 1 arguement");}
      TarRef tarRef = args[N-1]->tar();
      if (tarRef.is_null()) {throw TarskiException("bbwb argument not a Tarski formula");}
      TFormRef tRef = tarRef->getValue();
      TAndRef A = asa<TAndObj>(tRef);
      if (A.is_null()) {
        throw TarskiException("ERROR - NOT A CONJUNCTION");
      }
      else if (A->size() == 0) {
        throw TarskiException("ERROR - EMTPY CONJUNCTION");
      }
      o.loadOptions(args);
      return A;
    }

  
  SRef BBWBComm::execute(SRef input, std::vector<SRef> &args) {
    TAndRef A;
    optionsHandler o(options);
    try {
      A = preProcess(args, o);
    }
    catch (TarskiException t) {
      return new ErrObj(t.what());
    }
    Boxer * b = new Boxer(A);
    LisRef l = b->genLisResult();
    if (o.getOpt(0)) b->prettyPrintResult();
    delete b;
    return l;
  }

}//namespace tarski
