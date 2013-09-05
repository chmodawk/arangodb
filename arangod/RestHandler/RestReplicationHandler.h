////////////////////////////////////////////////////////////////////////////////
/// @brief replication request handler
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2010-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_REST_HANDLER_REST_REPLICATION_HANDLER_H
#define TRIAGENS_REST_HANDLER_REST_REPLICATION_HANDLER_H 1

#include "RestHandler/RestVocbaseBaseHandler.h"
#include "HttpServer/HttpServer.h"
#include "VocBase/edge-collection.h"
#include "VocBase/replication-common.h"

using namespace triagens::basics;
using namespace triagens::rest;
using namespace std;

struct TRI_json_s;
struct TRI_replication_log_state_s;
struct TRI_transaction_collection_s;
struct TRI_vocbase_col_s;

// -----------------------------------------------------------------------------
// --SECTION--                                            RestReplicationHandler
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

namespace triagens {
  namespace arango {

////////////////////////////////////////////////////////////////////////////////
/// @brief replication request handler
////////////////////////////////////////////////////////////////////////////////

    class RestReplicationHandler : public RestVocbaseBaseHandler {

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

        RestReplicationHandler (rest::HttpRequest*, struct TRI_vocbase_s*);

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////

        ~RestReplicationHandler ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   Handler methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        bool isDirect ();

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        string const& queue () const;

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        Handler::status_e execute();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                             public static methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////
      
      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief comparator to sort collections
/// sort order is by collection type first (vertices before edges, this is
/// because edges depend on vertices being there), then name 
////////////////////////////////////////////////////////////////////////////////

        static int sortCollections (const void*,
                                    const void*); 

////////////////////////////////////////////////////////////////////////////////
/// @brief filter a collection based on collection attributes
////////////////////////////////////////////////////////////////////////////////

        static bool filterCollection (struct TRI_vocbase_col_s*, void*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   private methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief insert the applier action into an action list
////////////////////////////////////////////////////////////////////////////////

        void insertClient (TRI_voc_tick_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief determine chunk size from request
////////////////////////////////////////////////////////////////////////////////

        uint64_t determineChunkSize () const;

////////////////////////////////////////////////////////////////////////////////
/// @brief remotely start the replication logger
////////////////////////////////////////////////////////////////////////////////

        void handleCommandLoggerStart ();

////////////////////////////////////////////////////////////////////////////////
/// @brief remotely stop the replication logger
////////////////////////////////////////////////////////////////////////////////

        void handleCommandLoggerStop ();

////////////////////////////////////////////////////////////////////////////////
/// @brief return the state of the replication logger
////////////////////////////////////////////////////////////////////////////////

        void handleCommandLoggerState ();

////////////////////////////////////////////////////////////////////////////////
/// @brief return the configuration of the the replication logger
////////////////////////////////////////////////////////////////////////////////

        void handleCommandLoggerGetConfig ();

////////////////////////////////////////////////////////////////////////////////
/// @brief configure the replication logger
////////////////////////////////////////////////////////////////////////////////

        void handleCommandLoggerSetConfig ();

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a follow command for the replication log
////////////////////////////////////////////////////////////////////////////////

        void handleCommandLoggerFollow ();

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a batch command
////////////////////////////////////////////////////////////////////////////////
        
        void handleCommandBatch ();

////////////////////////////////////////////////////////////////////////////////
/// @brief return the inventory (current replication and collection state)
////////////////////////////////////////////////////////////////////////////////

        void handleCommandInventory ();

////////////////////////////////////////////////////////////////////////////////
/// @brief extract the collection id from JSON TODO: move
////////////////////////////////////////////////////////////////////////////////

        TRI_voc_cid_t getCid (struct TRI_json_s const*) const;

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a collection, based on the JSON provided TODO: move
////////////////////////////////////////////////////////////////////////////////
    
        int createCollection (struct TRI_json_s const*,
                              struct TRI_vocbase_col_s**,
                              TRI_server_id_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief restores the structure of a collection TODO MOVE
////////////////////////////////////////////////////////////////////////////////

        int processRestoreCollection (struct TRI_json_s* const,
                                      bool,
                                      TRI_server_id_t,
                                      std::string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a restore command for a specific collection
////////////////////////////////////////////////////////////////////////////////

        void handleCommandRestoreCollection ();

////////////////////////////////////////////////////////////////////////////////
/// @brief apply a single marker from the collection dump
////////////////////////////////////////////////////////////////////////////////

        int applyCollectionDumpMarker (struct TRI_transaction_collection_s*,
                                       TRI_replication_operation_e,
                                       const TRI_voc_key_t,
                                       const TRI_voc_rid_t,
                                       struct TRI_json_s const*,
                                       std::string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief restores the data of a collection TODO MOVE
////////////////////////////////////////////////////////////////////////////////

        int processRestoreDataBatch (struct TRI_transaction_collection_s*,
                                     TRI_server_id_t,
                                     std::string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief restores the data of a collection TODO
////////////////////////////////////////////////////////////////////////////////

        int processRestoreData (TRI_voc_cid_t,
                                TRI_server_id_t,
                                std::string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a restore command for a specific collection
////////////////////////////////////////////////////////////////////////////////

        void handleCommandRestoreData ();

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a dump command for a specific collection
////////////////////////////////////////////////////////////////////////////////

        void handleCommandDump ();

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a sync command
////////////////////////////////////////////////////////////////////////////////

        void handleCommandSync ();

////////////////////////////////////////////////////////////////////////////////
/// @brief handle a server-id command
////////////////////////////////////////////////////////////////////////////////

        void handleCommandServerId ();

////////////////////////////////////////////////////////////////////////////////
/// @brief return the configuration of the the replication applier
////////////////////////////////////////////////////////////////////////////////

        void handleCommandApplierGetConfig ();

////////////////////////////////////////////////////////////////////////////////
/// @brief configure the replication applier
////////////////////////////////////////////////////////////////////////////////

        void handleCommandApplierSetConfig ();

////////////////////////////////////////////////////////////////////////////////
/// @brief start the replication applier
////////////////////////////////////////////////////////////////////////////////

        void handleCommandApplierStart ();

////////////////////////////////////////////////////////////////////////////////
/// @brief stop the replication applier
////////////////////////////////////////////////////////////////////////////////

        void handleCommandApplierStop ();

////////////////////////////////////////////////////////////////////////////////
/// @brief return the state of the replication applier
////////////////////////////////////////////////////////////////////////////////

        void handleCommandApplierGetState ();

////////////////////////////////////////////////////////////////////////////////
/// @brief delete the replication applier state
////////////////////////////////////////////////////////////////////////////////

        void handleCommandApplierDeleteState ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief minimum chunk size
////////////////////////////////////////////////////////////////////////////////
  
        static const uint64_t defaultChunkSize;

////////////////////////////////////////////////////////////////////////////////
/// @brief maximum chunk size
////////////////////////////////////////////////////////////////////////////////

        static const uint64_t maxChunkSize;

     };
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
