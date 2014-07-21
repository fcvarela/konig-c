// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: graphproto.proto

#ifndef PROTOBUF_graphproto_2eproto__INCLUDED
#define PROTOBUF_graphproto_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/service.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace graphproto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_graphproto_2eproto();
void protobuf_AssignDesc_graphproto_2eproto();
void protobuf_ShutdownFile_graphproto_2eproto();

class GraphResponse;
class GraphRequest;

// ===================================================================

class GraphResponse : public ::google::protobuf::Message {
 public:
  GraphResponse();
  virtual ~GraphResponse();

  GraphResponse(const GraphResponse& from);

  inline GraphResponse& operator=(const GraphResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GraphResponse& default_instance();

  void Swap(GraphResponse* other);

  // implements Message ----------------------------------------------

  GraphResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GraphResponse& from);
  void MergeFrom(const GraphResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint64 obj_id = 1;
  inline bool has_obj_id() const;
  inline void clear_obj_id();
  static const int kObjIdFieldNumber = 1;
  inline ::google::protobuf::uint64 obj_id() const;
  inline void set_obj_id(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:graphproto.GraphResponse)
 private:
  inline void set_has_obj_id();
  inline void clear_has_obj_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 obj_id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_graphproto_2eproto();
  friend void protobuf_AssignDesc_graphproto_2eproto();
  friend void protobuf_ShutdownFile_graphproto_2eproto();

  void InitAsDefaultInstance();
  static GraphResponse* default_instance_;
};
// -------------------------------------------------------------------

class GraphRequest : public ::google::protobuf::Message {
 public:
  GraphRequest();
  virtual ~GraphRequest();

  GraphRequest(const GraphRequest& from);

  inline GraphRequest& operator=(const GraphRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GraphRequest& default_instance();

  void Swap(GraphRequest* other);

  // implements Message ----------------------------------------------

  GraphRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GraphRequest& from);
  void MergeFrom(const GraphRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint64 obj_id1 = 1;
  inline bool has_obj_id1() const;
  inline void clear_obj_id1();
  static const int kObjId1FieldNumber = 1;
  inline ::google::protobuf::uint64 obj_id1() const;
  inline void set_obj_id1(::google::protobuf::uint64 value);

  // optional uint64 obj_id2 = 2;
  inline bool has_obj_id2() const;
  inline void clear_obj_id2();
  static const int kObjId2FieldNumber = 2;
  inline ::google::protobuf::uint64 obj_id2() const;
  inline void set_obj_id2(::google::protobuf::uint64 value);

  // optional uint64 obj_id3 = 3;
  inline bool has_obj_id3() const;
  inline void clear_obj_id3();
  static const int kObjId3FieldNumber = 3;
  inline ::google::protobuf::uint64 obj_id3() const;
  inline void set_obj_id3(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:graphproto.GraphRequest)
 private:
  inline void set_has_obj_id1();
  inline void clear_has_obj_id1();
  inline void set_has_obj_id2();
  inline void clear_has_obj_id2();
  inline void set_has_obj_id3();
  inline void clear_has_obj_id3();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 obj_id1_;
  ::google::protobuf::uint64 obj_id2_;
  ::google::protobuf::uint64 obj_id3_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_graphproto_2eproto();
  friend void protobuf_AssignDesc_graphproto_2eproto();
  friend void protobuf_ShutdownFile_graphproto_2eproto();

  void InitAsDefaultInstance();
  static GraphRequest* default_instance_;
};
// ===================================================================

class GraphService_Stub;

class GraphService : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline GraphService() {};
 public:
  virtual ~GraphService();

  typedef GraphService_Stub Stub;

  static const ::google::protobuf::ServiceDescriptor* descriptor();

  virtual void add_graph(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void add_vertex(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void add_edge(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void delete_graph(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void delete_vertex(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void delete_edge(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GraphService);
};

class GraphService_Stub : public GraphService {
 public:
  GraphService_Stub(::google::protobuf::RpcChannel* channel);
  GraphService_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~GraphService_Stub();

  inline ::google::protobuf::RpcChannel* channel() { return channel_; }

  // implements GraphService ------------------------------------------

  void add_graph(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  void add_vertex(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  void add_edge(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  void delete_graph(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  void delete_vertex(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
  void delete_edge(::google::protobuf::RpcController* controller,
                       const ::graphproto::GraphRequest* request,
                       ::graphproto::GraphResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GraphService_Stub);
};


// ===================================================================


// ===================================================================

// GraphResponse

// optional uint64 obj_id = 1;
inline bool GraphResponse::has_obj_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GraphResponse::set_has_obj_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GraphResponse::clear_has_obj_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GraphResponse::clear_obj_id() {
  obj_id_ = GOOGLE_ULONGLONG(0);
  clear_has_obj_id();
}
inline ::google::protobuf::uint64 GraphResponse::obj_id() const {
  return obj_id_;
}
inline void GraphResponse::set_obj_id(::google::protobuf::uint64 value) {
  set_has_obj_id();
  obj_id_ = value;
}

// -------------------------------------------------------------------

// GraphRequest

// optional uint64 obj_id1 = 1;
inline bool GraphRequest::has_obj_id1() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GraphRequest::set_has_obj_id1() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GraphRequest::clear_has_obj_id1() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GraphRequest::clear_obj_id1() {
  obj_id1_ = GOOGLE_ULONGLONG(0);
  clear_has_obj_id1();
}
inline ::google::protobuf::uint64 GraphRequest::obj_id1() const {
  return obj_id1_;
}
inline void GraphRequest::set_obj_id1(::google::protobuf::uint64 value) {
  set_has_obj_id1();
  obj_id1_ = value;
}

// optional uint64 obj_id2 = 2;
inline bool GraphRequest::has_obj_id2() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GraphRequest::set_has_obj_id2() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GraphRequest::clear_has_obj_id2() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GraphRequest::clear_obj_id2() {
  obj_id2_ = GOOGLE_ULONGLONG(0);
  clear_has_obj_id2();
}
inline ::google::protobuf::uint64 GraphRequest::obj_id2() const {
  return obj_id2_;
}
inline void GraphRequest::set_obj_id2(::google::protobuf::uint64 value) {
  set_has_obj_id2();
  obj_id2_ = value;
}

// optional uint64 obj_id3 = 3;
inline bool GraphRequest::has_obj_id3() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GraphRequest::set_has_obj_id3() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GraphRequest::clear_has_obj_id3() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GraphRequest::clear_obj_id3() {
  obj_id3_ = GOOGLE_ULONGLONG(0);
  clear_has_obj_id3();
}
inline ::google::protobuf::uint64 GraphRequest::obj_id3() const {
  return obj_id3_;
}
inline void GraphRequest::set_obj_id3(::google::protobuf::uint64 value) {
  set_has_obj_id3();
  obj_id3_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace graphproto

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_graphproto_2eproto__INCLUDED