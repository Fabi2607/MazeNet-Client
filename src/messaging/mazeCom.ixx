// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef MAZE_COM_IXX
#define MAZE_COM_IXX

// Begin prologue.
//
//
// End prologue.

// MazeComType
// 

inline
MazeComType::
MazeComType (value v)
: ::xml_schema::string (_xsd_MazeComType_literals_[v])
{
}

inline
MazeComType::
MazeComType (const char* v)
: ::xml_schema::string (v)
{
}

inline
MazeComType::
MazeComType (const ::std::string& v)
: ::xml_schema::string (v)
{
}

inline
MazeComType::
MazeComType (const ::xml_schema::string& v)
: ::xml_schema::string (v)
{
}

inline
MazeComType::
MazeComType (const MazeComType& v,
             ::xml_schema::flags f,
             ::xml_schema::container* c)
: ::xml_schema::string (v, f, c)
{
}

inline
MazeComType& MazeComType::
operator= (value v)
{
  static_cast< ::xml_schema::string& > (*this) = 
  ::xml_schema::string (_xsd_MazeComType_literals_[v]);

  return *this;
}


// treasureType
// 

inline
treasureType::
treasureType (value v)
: ::xml_schema::string (_xsd_treasureType_literals_[v])
{
}

inline
treasureType::
treasureType (const char* v)
: ::xml_schema::string (v)
{
}

inline
treasureType::
treasureType (const ::std::string& v)
: ::xml_schema::string (v)
{
}

inline
treasureType::
treasureType (const ::xml_schema::string& v)
: ::xml_schema::string (v)
{
}

inline
treasureType::
treasureType (const treasureType& v,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::string (v, f, c)
{
}

inline
treasureType& treasureType::
operator= (value v)
{
  static_cast< ::xml_schema::string& > (*this) = 
  ::xml_schema::string (_xsd_treasureType_literals_[v]);

  return *this;
}


// ErrorType
// 

inline
ErrorType::
ErrorType (value v)
: ::xml_schema::string (_xsd_ErrorType_literals_[v])
{
}

inline
ErrorType::
ErrorType (const char* v)
: ::xml_schema::string (v)
{
}

inline
ErrorType::
ErrorType (const ::std::string& v)
: ::xml_schema::string (v)
{
}

inline
ErrorType::
ErrorType (const ::xml_schema::string& v)
: ::xml_schema::string (v)
{
}

inline
ErrorType::
ErrorType (const ErrorType& v,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
: ::xml_schema::string (v, f, c)
{
}

inline
ErrorType& ErrorType::
operator= (value v)
{
  static_cast< ::xml_schema::string& > (*this) = 
  ::xml_schema::string (_xsd_ErrorType_literals_[v]);

  return *this;
}


// cardType
// 

inline
const cardType::openings_type& cardType::
openings () const
{
  return this->openings_.get ();
}

inline
cardType::openings_type& cardType::
openings ()
{
  return this->openings_.get ();
}

inline
void cardType::
openings (const openings_type& x)
{
  this->openings_.set (x);
}

inline
void cardType::
openings (::std::unique_ptr< openings_type > x)
{
  this->openings_.set (std::move (x));
}

inline
const cardType::pin_type& cardType::
pin () const
{
  return this->pin_.get ();
}

inline
cardType::pin_type& cardType::
pin ()
{
  return this->pin_.get ();
}

inline
void cardType::
pin (const pin_type& x)
{
  this->pin_.set (x);
}

inline
void cardType::
pin (::std::unique_ptr< pin_type > x)
{
  this->pin_.set (std::move (x));
}

inline
const cardType::treasure_optional& cardType::
treasure () const
{
  return this->treasure_;
}

inline
cardType::treasure_optional& cardType::
treasure ()
{
  return this->treasure_;
}

inline
void cardType::
treasure (const treasure_type& x)
{
  this->treasure_.set (x);
}

inline
void cardType::
treasure (const treasure_optional& x)
{
  this->treasure_ = x;
}

inline
void cardType::
treasure (::std::unique_ptr< treasure_type > x)
{
  this->treasure_.set (std::move (x));
}


// boardType
// 

inline
const boardType::row_sequence& boardType::
row () const
{
  return this->row_;
}

inline
boardType::row_sequence& boardType::
row ()
{
  return this->row_;
}

inline
void boardType::
row (const row_sequence& s)
{
  this->row_ = s;
}

inline
const boardType::shiftCard_type& boardType::
shiftCard () const
{
  return this->shiftCard_.get ();
}

inline
boardType::shiftCard_type& boardType::
shiftCard ()
{
  return this->shiftCard_.get ();
}

inline
void boardType::
shiftCard (const shiftCard_type& x)
{
  this->shiftCard_.set (x);
}

inline
void boardType::
shiftCard (::std::unique_ptr< shiftCard_type > x)
{
  this->shiftCard_.set (std::move (x));
}

inline
const boardType::forbidden_optional& boardType::
forbidden () const
{
  return this->forbidden_;
}

inline
boardType::forbidden_optional& boardType::
forbidden ()
{
  return this->forbidden_;
}

inline
void boardType::
forbidden (const forbidden_type& x)
{
  this->forbidden_.set (x);
}

inline
void boardType::
forbidden (const forbidden_optional& x)
{
  this->forbidden_ = x;
}

inline
void boardType::
forbidden (::std::unique_ptr< forbidden_type > x)
{
  this->forbidden_.set (std::move (x));
}


// positionType
// 

inline
const positionType::row_type& positionType::
row () const
{
  return this->row_.get ();
}

inline
positionType::row_type& positionType::
row ()
{
  return this->row_.get ();
}

inline
void positionType::
row (const row_type& x)
{
  this->row_.set (x);
}

inline
const positionType::col_type& positionType::
col () const
{
  return this->col_.get ();
}

inline
positionType::col_type& positionType::
col ()
{
  return this->col_.get ();
}

inline
void positionType::
col (const col_type& x)
{
  this->col_.set (x);
}


// LoginMessageType
// 

inline
const LoginMessageType::name_type& LoginMessageType::
name () const
{
  return this->name_.get ();
}

inline
LoginMessageType::name_type& LoginMessageType::
name ()
{
  return this->name_.get ();
}

inline
void LoginMessageType::
name (const name_type& x)
{
  this->name_.set (x);
}

inline
void LoginMessageType::
name (::std::unique_ptr< name_type > x)
{
  this->name_.set (std::move (x));
}


// LoginReplyMessageType
// 

inline
const LoginReplyMessageType::newID_type& LoginReplyMessageType::
newID () const
{
  return this->newID_.get ();
}

inline
LoginReplyMessageType::newID_type& LoginReplyMessageType::
newID ()
{
  return this->newID_.get ();
}

inline
void LoginReplyMessageType::
newID (const newID_type& x)
{
  this->newID_.set (x);
}


// AwaitMoveMessageType
// 

inline
const AwaitMoveMessageType::board_type& AwaitMoveMessageType::
board () const
{
  return this->board_.get ();
}

inline
AwaitMoveMessageType::board_type& AwaitMoveMessageType::
board ()
{
  return this->board_.get ();
}

inline
void AwaitMoveMessageType::
board (const board_type& x)
{
  this->board_.set (x);
}

inline
void AwaitMoveMessageType::
board (::std::unique_ptr< board_type > x)
{
  this->board_.set (std::move (x));
}

inline
const AwaitMoveMessageType::treasuresToGo_sequence& AwaitMoveMessageType::
treasuresToGo () const
{
  return this->treasuresToGo_;
}

inline
AwaitMoveMessageType::treasuresToGo_sequence& AwaitMoveMessageType::
treasuresToGo ()
{
  return this->treasuresToGo_;
}

inline
void AwaitMoveMessageType::
treasuresToGo (const treasuresToGo_sequence& s)
{
  this->treasuresToGo_ = s;
}

inline
const AwaitMoveMessageType::treasure_type& AwaitMoveMessageType::
treasure () const
{
  return this->treasure_.get ();
}

inline
AwaitMoveMessageType::treasure_type& AwaitMoveMessageType::
treasure ()
{
  return this->treasure_.get ();
}

inline
void AwaitMoveMessageType::
treasure (const treasure_type& x)
{
  this->treasure_.set (x);
}

inline
void AwaitMoveMessageType::
treasure (::std::unique_ptr< treasure_type > x)
{
  this->treasure_.set (std::move (x));
}


// TreasuresToGoType
// 

inline
const TreasuresToGoType::player_type& TreasuresToGoType::
player () const
{
  return this->player_.get ();
}

inline
TreasuresToGoType::player_type& TreasuresToGoType::
player ()
{
  return this->player_.get ();
}

inline
void TreasuresToGoType::
player (const player_type& x)
{
  this->player_.set (x);
}

inline
const TreasuresToGoType::treasures_type& TreasuresToGoType::
treasures () const
{
  return this->treasures_.get ();
}

inline
TreasuresToGoType::treasures_type& TreasuresToGoType::
treasures ()
{
  return this->treasures_.get ();
}

inline
void TreasuresToGoType::
treasures (const treasures_type& x)
{
  this->treasures_.set (x);
}


// MoveMessageType
// 

inline
const MoveMessageType::shiftPosition_type& MoveMessageType::
shiftPosition () const
{
  return this->shiftPosition_.get ();
}

inline
MoveMessageType::shiftPosition_type& MoveMessageType::
shiftPosition ()
{
  return this->shiftPosition_.get ();
}

inline
void MoveMessageType::
shiftPosition (const shiftPosition_type& x)
{
  this->shiftPosition_.set (x);
}

inline
void MoveMessageType::
shiftPosition (::std::unique_ptr< shiftPosition_type > x)
{
  this->shiftPosition_.set (std::move (x));
}

inline
const MoveMessageType::newPinPos_type& MoveMessageType::
newPinPos () const
{
  return this->newPinPos_.get ();
}

inline
MoveMessageType::newPinPos_type& MoveMessageType::
newPinPos ()
{
  return this->newPinPos_.get ();
}

inline
void MoveMessageType::
newPinPos (const newPinPos_type& x)
{
  this->newPinPos_.set (x);
}

inline
void MoveMessageType::
newPinPos (::std::unique_ptr< newPinPos_type > x)
{
  this->newPinPos_.set (std::move (x));
}

inline
const MoveMessageType::shiftCard_type& MoveMessageType::
shiftCard () const
{
  return this->shiftCard_.get ();
}

inline
MoveMessageType::shiftCard_type& MoveMessageType::
shiftCard ()
{
  return this->shiftCard_.get ();
}

inline
void MoveMessageType::
shiftCard (const shiftCard_type& x)
{
  this->shiftCard_.set (x);
}

inline
void MoveMessageType::
shiftCard (::std::unique_ptr< shiftCard_type > x)
{
  this->shiftCard_.set (std::move (x));
}


// AcceptMessageType
// 

inline
const AcceptMessageType::accept_type& AcceptMessageType::
accept () const
{
  return this->accept_.get ();
}

inline
AcceptMessageType::accept_type& AcceptMessageType::
accept ()
{
  return this->accept_.get ();
}

inline
void AcceptMessageType::
accept (const accept_type& x)
{
  this->accept_.set (x);
}

inline
const AcceptMessageType::errorCode_type& AcceptMessageType::
errorCode () const
{
  return this->errorCode_.get ();
}

inline
AcceptMessageType::errorCode_type& AcceptMessageType::
errorCode ()
{
  return this->errorCode_.get ();
}

inline
void AcceptMessageType::
errorCode (const errorCode_type& x)
{
  this->errorCode_.set (x);
}

inline
void AcceptMessageType::
errorCode (::std::unique_ptr< errorCode_type > x)
{
  this->errorCode_.set (std::move (x));
}


// WinMessageType
// 

inline
const WinMessageType::board_type& WinMessageType::
board () const
{
  return this->board_.get ();
}

inline
WinMessageType::board_type& WinMessageType::
board ()
{
  return this->board_.get ();
}

inline
void WinMessageType::
board (const board_type& x)
{
  this->board_.set (x);
}

inline
void WinMessageType::
board (::std::unique_ptr< board_type > x)
{
  this->board_.set (std::move (x));
}

inline
const WinMessageType::winner_type& WinMessageType::
winner () const
{
  return this->winner_.get ();
}

inline
WinMessageType::winner_type& WinMessageType::
winner ()
{
  return this->winner_.get ();
}

inline
void WinMessageType::
winner (const winner_type& x)
{
  this->winner_.set (x);
}

inline
void WinMessageType::
winner (::std::unique_ptr< winner_type > x)
{
  this->winner_.set (std::move (x));
}


// DisconnectMessageType
// 

inline
const DisconnectMessageType::name_type& DisconnectMessageType::
name () const
{
  return this->name_.get ();
}

inline
DisconnectMessageType::name_type& DisconnectMessageType::
name ()
{
  return this->name_.get ();
}

inline
void DisconnectMessageType::
name (const name_type& x)
{
  this->name_.set (x);
}

inline
void DisconnectMessageType::
name (::std::unique_ptr< name_type > x)
{
  this->name_.set (std::move (x));
}

inline
const DisconnectMessageType::erroCode_type& DisconnectMessageType::
erroCode () const
{
  return this->erroCode_.get ();
}

inline
DisconnectMessageType::erroCode_type& DisconnectMessageType::
erroCode ()
{
  return this->erroCode_.get ();
}

inline
void DisconnectMessageType::
erroCode (const erroCode_type& x)
{
  this->erroCode_.set (x);
}

inline
void DisconnectMessageType::
erroCode (::std::unique_ptr< erroCode_type > x)
{
  this->erroCode_.set (std::move (x));
}


// openings
// 

inline
const openings::top_type& openings::
top () const
{
  return this->top_.get ();
}

inline
openings::top_type& openings::
top ()
{
  return this->top_.get ();
}

inline
void openings::
top (const top_type& x)
{
  this->top_.set (x);
}

inline
const openings::bottom_type& openings::
bottom () const
{
  return this->bottom_.get ();
}

inline
openings::bottom_type& openings::
bottom ()
{
  return this->bottom_.get ();
}

inline
void openings::
bottom (const bottom_type& x)
{
  this->bottom_.set (x);
}

inline
const openings::left_type& openings::
left () const
{
  return this->left_.get ();
}

inline
openings::left_type& openings::
left ()
{
  return this->left_.get ();
}

inline
void openings::
left (const left_type& x)
{
  this->left_.set (x);
}

inline
const openings::right_type& openings::
right () const
{
  return this->right_.get ();
}

inline
openings::right_type& openings::
right ()
{
  return this->right_.get ();
}

inline
void openings::
right (const right_type& x)
{
  this->right_.set (x);
}


// pin
// 

inline
const pin::playerID_sequence& pin::
playerID () const
{
  return this->playerID_;
}

inline
pin::playerID_sequence& pin::
playerID ()
{
  return this->playerID_;
}

inline
void pin::
playerID (const playerID_sequence& s)
{
  this->playerID_ = s;
}


// row
// 

inline
const row::col_sequence& row::
col () const
{
  return this->col_;
}

inline
row::col_sequence& row::
col ()
{
  return this->col_;
}

inline
void row::
col (const col_sequence& s)
{
  this->col_ = s;
}

inline
const row::OptionalAttirbute_optional& row::
OptionalAttirbute () const
{
  return this->OptionalAttirbute_;
}

inline
row::OptionalAttirbute_optional& row::
OptionalAttirbute ()
{
  return this->OptionalAttirbute_;
}

inline
void row::
OptionalAttirbute (const OptionalAttirbute_type& x)
{
  this->OptionalAttirbute_.set (x);
}

inline
void row::
OptionalAttirbute (const OptionalAttirbute_optional& x)
{
  this->OptionalAttirbute_ = x;
}

inline
void row::
OptionalAttirbute (::std::unique_ptr< OptionalAttirbute_type > x)
{
  this->OptionalAttirbute_.set (std::move (x));
}


// MazeCom
// 

inline
const MazeCom::LoginMessage_optional& MazeCom::
LoginMessage () const
{
  return this->LoginMessage_;
}

inline
MazeCom::LoginMessage_optional& MazeCom::
LoginMessage ()
{
  return this->LoginMessage_;
}

inline
void MazeCom::
LoginMessage (const LoginMessage_type& x)
{
  this->LoginMessage_.set (x);
}

inline
void MazeCom::
LoginMessage (const LoginMessage_optional& x)
{
  this->LoginMessage_ = x;
}

inline
void MazeCom::
LoginMessage (::std::unique_ptr< LoginMessage_type > x)
{
  this->LoginMessage_.set (std::move (x));
}

inline
const MazeCom::LoginReplyMessage_optional& MazeCom::
LoginReplyMessage () const
{
  return this->LoginReplyMessage_;
}

inline
MazeCom::LoginReplyMessage_optional& MazeCom::
LoginReplyMessage ()
{
  return this->LoginReplyMessage_;
}

inline
void MazeCom::
LoginReplyMessage (const LoginReplyMessage_type& x)
{
  this->LoginReplyMessage_.set (x);
}

inline
void MazeCom::
LoginReplyMessage (const LoginReplyMessage_optional& x)
{
  this->LoginReplyMessage_ = x;
}

inline
void MazeCom::
LoginReplyMessage (::std::unique_ptr< LoginReplyMessage_type > x)
{
  this->LoginReplyMessage_.set (std::move (x));
}

inline
const MazeCom::AwaitMoveMessage_optional& MazeCom::
AwaitMoveMessage () const
{
  return this->AwaitMoveMessage_;
}

inline
MazeCom::AwaitMoveMessage_optional& MazeCom::
AwaitMoveMessage ()
{
  return this->AwaitMoveMessage_;
}

inline
void MazeCom::
AwaitMoveMessage (const AwaitMoveMessage_type& x)
{
  this->AwaitMoveMessage_.set (x);
}

inline
void MazeCom::
AwaitMoveMessage (const AwaitMoveMessage_optional& x)
{
  this->AwaitMoveMessage_ = x;
}

inline
void MazeCom::
AwaitMoveMessage (::std::unique_ptr< AwaitMoveMessage_type > x)
{
  this->AwaitMoveMessage_.set (std::move (x));
}

inline
const MazeCom::MoveMessage_optional& MazeCom::
MoveMessage () const
{
  return this->MoveMessage_;
}

inline
MazeCom::MoveMessage_optional& MazeCom::
MoveMessage ()
{
  return this->MoveMessage_;
}

inline
void MazeCom::
MoveMessage (const MoveMessage_type& x)
{
  this->MoveMessage_.set (x);
}

inline
void MazeCom::
MoveMessage (const MoveMessage_optional& x)
{
  this->MoveMessage_ = x;
}

inline
void MazeCom::
MoveMessage (::std::unique_ptr< MoveMessage_type > x)
{
  this->MoveMessage_.set (std::move (x));
}

inline
const MazeCom::AcceptMessage_optional& MazeCom::
AcceptMessage () const
{
  return this->AcceptMessage_;
}

inline
MazeCom::AcceptMessage_optional& MazeCom::
AcceptMessage ()
{
  return this->AcceptMessage_;
}

inline
void MazeCom::
AcceptMessage (const AcceptMessage_type& x)
{
  this->AcceptMessage_.set (x);
}

inline
void MazeCom::
AcceptMessage (const AcceptMessage_optional& x)
{
  this->AcceptMessage_ = x;
}

inline
void MazeCom::
AcceptMessage (::std::unique_ptr< AcceptMessage_type > x)
{
  this->AcceptMessage_.set (std::move (x));
}

inline
const MazeCom::WinMessage_optional& MazeCom::
WinMessage () const
{
  return this->WinMessage_;
}

inline
MazeCom::WinMessage_optional& MazeCom::
WinMessage ()
{
  return this->WinMessage_;
}

inline
void MazeCom::
WinMessage (const WinMessage_type& x)
{
  this->WinMessage_.set (x);
}

inline
void MazeCom::
WinMessage (const WinMessage_optional& x)
{
  this->WinMessage_ = x;
}

inline
void MazeCom::
WinMessage (::std::unique_ptr< WinMessage_type > x)
{
  this->WinMessage_.set (std::move (x));
}

inline
const MazeCom::DisconnectMessage_optional& MazeCom::
DisconnectMessage () const
{
  return this->DisconnectMessage_;
}

inline
MazeCom::DisconnectMessage_optional& MazeCom::
DisconnectMessage ()
{
  return this->DisconnectMessage_;
}

inline
void MazeCom::
DisconnectMessage (const DisconnectMessage_type& x)
{
  this->DisconnectMessage_.set (x);
}

inline
void MazeCom::
DisconnectMessage (const DisconnectMessage_optional& x)
{
  this->DisconnectMessage_ = x;
}

inline
void MazeCom::
DisconnectMessage (::std::unique_ptr< DisconnectMessage_type > x)
{
  this->DisconnectMessage_.set (std::move (x));
}

inline
const MazeCom::mcType_type& MazeCom::
mcType () const
{
  return this->mcType_.get ();
}

inline
MazeCom::mcType_type& MazeCom::
mcType ()
{
  return this->mcType_.get ();
}

inline
void MazeCom::
mcType (const mcType_type& x)
{
  this->mcType_.set (x);
}

inline
void MazeCom::
mcType (::std::unique_ptr< mcType_type > x)
{
  this->mcType_.set (std::move (x));
}

inline
const MazeCom::id_type& MazeCom::
id () const
{
  return this->id_.get ();
}

inline
MazeCom::id_type& MazeCom::
id ()
{
  return this->id_.get ();
}

inline
void MazeCom::
id (const id_type& x)
{
  this->id_.set (x);
}


// winner
// 

inline
const winner::id_type& winner::
id () const
{
  return this->id_.get ();
}

inline
winner::id_type& winner::
id ()
{
  return this->id_.get ();
}

inline
void winner::
id (const id_type& x)
{
  this->id_.set (x);
}


// Begin epilogue.
//
//
// End epilogue.

#endif // MAZE_COM_IXX
