#ifndef _BIP_Engine_Atom_HPP_
#define _BIP_Engine_Atom_HPP_

// inherited classes
#include <AtomItf.hpp>
#include "AtomExportPort.hpp"
#include "AtomExportData.hpp"
#include "AtomInternalPort.hpp"
#include "Component.hpp"
#include "ExecuteAtomJob.hpp"

class BipError;
class Compound;

class Atom : public virtual ComponentItf, public Component, public AtomItf {
 public:
  // constructors
  Atom(const string &name);

  // destructor
  virtual ~Atom();

  virtual BipError &execute(PortValue &portValue) = 0;
  virtual string toString() const { return "-"; };

  // specific
  BipError &execute(AtomInternalPort &internalPort);
  void reset();

  ExecuteAtomJob &executeJob() { return mExecuteJob; }

 protected:
  // references accessors
  void addInternalPort(AtomInternalPort &internalPort) {
    mInternalPorts[internalPort.name()] = &internalPort;
    internalPort.setHolder(*this);
  }

  void addPort(AtomExportPort &port) {
    mPorts[port.name()] = &port;
    port.setHolder(*this);

    Component::addPort(port);

    //port.reset().dependsOn(executeJob());
  }

  void addData(AtomExportData &data) {
    mData[data.name()] = &data;
    data.setHolder(*this);
    Component::addData(data);
  }

  // specific
  ExecuteAtomJob mExecuteJob;

  friend ostream& operator<<(ostream &o, const Atom &atom);
  friend ostream& operator<<(ostream &o, const Atom *atom);
};

#endif // _BIP_Engine_Atom_HPP_
