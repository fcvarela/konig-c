// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: graphproto.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "graphproto.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace graphproto {

namespace {

const ::google::protobuf::Descriptor* GraphResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GraphResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* GraphRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GraphRequest_reflection_ = NULL;
const ::google::protobuf::ServiceDescriptor* GraphService_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_graphproto_2eproto() {
  protobuf_AddDesc_graphproto_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "graphproto.proto");
  GOOGLE_CHECK(file != NULL);
  GraphResponse_descriptor_ = file->message_type(0);
  static const int GraphResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphResponse, obj_id_),
  };
  GraphResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GraphResponse_descriptor_,
      GraphResponse::default_instance_,
      GraphResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GraphResponse));
  GraphRequest_descriptor_ = file->message_type(1);
  static const int GraphRequest_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphRequest, obj_id1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphRequest, obj_id2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphRequest, obj_id3_),
  };
  GraphRequest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GraphRequest_descriptor_,
      GraphRequest::default_instance_,
      GraphRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphRequest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GraphRequest, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GraphRequest));
  GraphService_descriptor_ = file->service(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_graphproto_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GraphResponse_descriptor_, &GraphResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GraphRequest_descriptor_, &GraphRequest::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_graphproto_2eproto() {
  delete GraphResponse::default_instance_;
  delete GraphResponse_reflection_;
  delete GraphRequest::default_instance_;
  delete GraphRequest_reflection_;
}

void protobuf_AddDesc_graphproto_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020graphproto.proto\022\ngraphproto\"\037\n\rGraphR"
    "esponse\022\016\n\006obj_id\030\001 \001(\004\"A\n\014GraphRequest\022"
    "\017\n\007obj_id1\030\001 \001(\004\022\017\n\007obj_id2\030\002 \001(\004\022\017\n\007obj"
    "_id3\030\003 \001(\0042\243\003\n\014GraphService\022@\n\tadd_graph"
    "\022\030.graphproto.GraphRequest\032\031.graphproto."
    "GraphResponse\022A\n\nadd_vertex\022\030.graphproto"
    ".GraphRequest\032\031.graphproto.GraphResponse"
    "\022\?\n\010add_edge\022\030.graphproto.GraphRequest\032\031"
    ".graphproto.GraphResponse\022C\n\014delete_grap"
    "h\022\030.graphproto.GraphRequest\032\031.graphproto"
    ".GraphResponse\022D\n\rdelete_vertex\022\030.graphp"
    "roto.GraphRequest\032\031.graphproto.GraphResp"
    "onse\022B\n\013delete_edge\022\030.graphproto.GraphRe"
    "quest\032\031.graphproto.GraphResponseB\003\200\001\001", 557);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "graphproto.proto", &protobuf_RegisterTypes);
  GraphResponse::default_instance_ = new GraphResponse();
  GraphRequest::default_instance_ = new GraphRequest();
  GraphResponse::default_instance_->InitAsDefaultInstance();
  GraphRequest::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_graphproto_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_graphproto_2eproto {
  StaticDescriptorInitializer_graphproto_2eproto() {
    protobuf_AddDesc_graphproto_2eproto();
  }
} static_descriptor_initializer_graphproto_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int GraphResponse::kObjIdFieldNumber;
#endif  // !_MSC_VER

GraphResponse::GraphResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GraphResponse::InitAsDefaultInstance() {
}

GraphResponse::GraphResponse(const GraphResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GraphResponse::SharedCtor() {
  _cached_size_ = 0;
  obj_id_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GraphResponse::~GraphResponse() {
  SharedDtor();
}

void GraphResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GraphResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GraphResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GraphResponse_descriptor_;
}

const GraphResponse& GraphResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_graphproto_2eproto();
  return *default_instance_;
}

GraphResponse* GraphResponse::default_instance_ = NULL;

GraphResponse* GraphResponse::New() const {
  return new GraphResponse;
}

void GraphResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    obj_id_ = GOOGLE_ULONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GraphResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint64 obj_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &obj_id_)));
          set_has_obj_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void GraphResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint64 obj_id = 1;
  if (has_obj_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->obj_id(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GraphResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint64 obj_id = 1;
  if (has_obj_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->obj_id(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GraphResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint64 obj_id = 1;
    if (has_obj_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->obj_id());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GraphResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GraphResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GraphResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GraphResponse::MergeFrom(const GraphResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_obj_id()) {
      set_obj_id(from.obj_id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GraphResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GraphResponse::CopyFrom(const GraphResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GraphResponse::IsInitialized() const {

  return true;
}

void GraphResponse::Swap(GraphResponse* other) {
  if (other != this) {
    std::swap(obj_id_, other->obj_id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GraphResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GraphResponse_descriptor_;
  metadata.reflection = GraphResponse_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GraphRequest::kObjId1FieldNumber;
const int GraphRequest::kObjId2FieldNumber;
const int GraphRequest::kObjId3FieldNumber;
#endif  // !_MSC_VER

GraphRequest::GraphRequest()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GraphRequest::InitAsDefaultInstance() {
}

GraphRequest::GraphRequest(const GraphRequest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GraphRequest::SharedCtor() {
  _cached_size_ = 0;
  obj_id1_ = GOOGLE_ULONGLONG(0);
  obj_id2_ = GOOGLE_ULONGLONG(0);
  obj_id3_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GraphRequest::~GraphRequest() {
  SharedDtor();
}

void GraphRequest::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GraphRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GraphRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GraphRequest_descriptor_;
}

const GraphRequest& GraphRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_graphproto_2eproto();
  return *default_instance_;
}

GraphRequest* GraphRequest::default_instance_ = NULL;

GraphRequest* GraphRequest::New() const {
  return new GraphRequest;
}

void GraphRequest::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    obj_id1_ = GOOGLE_ULONGLONG(0);
    obj_id2_ = GOOGLE_ULONGLONG(0);
    obj_id3_ = GOOGLE_ULONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GraphRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint64 obj_id1 = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &obj_id1_)));
          set_has_obj_id1();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_obj_id2;
        break;
      }

      // optional uint64 obj_id2 = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_obj_id2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &obj_id2_)));
          set_has_obj_id2();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_obj_id3;
        break;
      }

      // optional uint64 obj_id3 = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_obj_id3:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &obj_id3_)));
          set_has_obj_id3();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void GraphRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint64 obj_id1 = 1;
  if (has_obj_id1()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->obj_id1(), output);
  }

  // optional uint64 obj_id2 = 2;
  if (has_obj_id2()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(2, this->obj_id2(), output);
  }

  // optional uint64 obj_id3 = 3;
  if (has_obj_id3()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->obj_id3(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GraphRequest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint64 obj_id1 = 1;
  if (has_obj_id1()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->obj_id1(), target);
  }

  // optional uint64 obj_id2 = 2;
  if (has_obj_id2()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(2, this->obj_id2(), target);
  }

  // optional uint64 obj_id3 = 3;
  if (has_obj_id3()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->obj_id3(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GraphRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint64 obj_id1 = 1;
    if (has_obj_id1()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->obj_id1());
    }

    // optional uint64 obj_id2 = 2;
    if (has_obj_id2()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->obj_id2());
    }

    // optional uint64 obj_id3 = 3;
    if (has_obj_id3()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->obj_id3());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GraphRequest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GraphRequest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GraphRequest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GraphRequest::MergeFrom(const GraphRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_obj_id1()) {
      set_obj_id1(from.obj_id1());
    }
    if (from.has_obj_id2()) {
      set_obj_id2(from.obj_id2());
    }
    if (from.has_obj_id3()) {
      set_obj_id3(from.obj_id3());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GraphRequest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GraphRequest::CopyFrom(const GraphRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GraphRequest::IsInitialized() const {

  return true;
}

void GraphRequest::Swap(GraphRequest* other) {
  if (other != this) {
    std::swap(obj_id1_, other->obj_id1_);
    std::swap(obj_id2_, other->obj_id2_);
    std::swap(obj_id3_, other->obj_id3_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GraphRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GraphRequest_descriptor_;
  metadata.reflection = GraphRequest_reflection_;
  return metadata;
}


// ===================================================================

GraphService::~GraphService() {}

const ::google::protobuf::ServiceDescriptor* GraphService::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GraphService_descriptor_;
}

const ::google::protobuf::ServiceDescriptor* GraphService::GetDescriptor() {
  protobuf_AssignDescriptorsOnce();
  return GraphService_descriptor_;
}

void GraphService::add_graph(::google::protobuf::RpcController* controller,
                         const ::graphproto::GraphRequest*,
                         ::graphproto::GraphResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method add_graph() not implemented.");
  done->Run();
}

void GraphService::add_vertex(::google::protobuf::RpcController* controller,
                         const ::graphproto::GraphRequest*,
                         ::graphproto::GraphResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method add_vertex() not implemented.");
  done->Run();
}

void GraphService::add_edge(::google::protobuf::RpcController* controller,
                         const ::graphproto::GraphRequest*,
                         ::graphproto::GraphResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method add_edge() not implemented.");
  done->Run();
}

void GraphService::delete_graph(::google::protobuf::RpcController* controller,
                         const ::graphproto::GraphRequest*,
                         ::graphproto::GraphResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method delete_graph() not implemented.");
  done->Run();
}

void GraphService::delete_vertex(::google::protobuf::RpcController* controller,
                         const ::graphproto::GraphRequest*,
                         ::graphproto::GraphResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method delete_vertex() not implemented.");
  done->Run();
}

void GraphService::delete_edge(::google::protobuf::RpcController* controller,
                         const ::graphproto::GraphRequest*,
                         ::graphproto::GraphResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method delete_edge() not implemented.");
  done->Run();
}

void GraphService::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                             ::google::protobuf::RpcController* controller,
                             const ::google::protobuf::Message* request,
                             ::google::protobuf::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), GraphService_descriptor_);
  switch(method->index()) {
    case 0:
      add_graph(controller,
             ::google::protobuf::down_cast<const ::graphproto::GraphRequest*>(request),
             ::google::protobuf::down_cast< ::graphproto::GraphResponse*>(response),
             done);
      break;
    case 1:
      add_vertex(controller,
             ::google::protobuf::down_cast<const ::graphproto::GraphRequest*>(request),
             ::google::protobuf::down_cast< ::graphproto::GraphResponse*>(response),
             done);
      break;
    case 2:
      add_edge(controller,
             ::google::protobuf::down_cast<const ::graphproto::GraphRequest*>(request),
             ::google::protobuf::down_cast< ::graphproto::GraphResponse*>(response),
             done);
      break;
    case 3:
      delete_graph(controller,
             ::google::protobuf::down_cast<const ::graphproto::GraphRequest*>(request),
             ::google::protobuf::down_cast< ::graphproto::GraphResponse*>(response),
             done);
      break;
    case 4:
      delete_vertex(controller,
             ::google::protobuf::down_cast<const ::graphproto::GraphRequest*>(request),
             ::google::protobuf::down_cast< ::graphproto::GraphResponse*>(response),
             done);
      break;
    case 5:
      delete_edge(controller,
             ::google::protobuf::down_cast<const ::graphproto::GraphRequest*>(request),
             ::google::protobuf::down_cast< ::graphproto::GraphResponse*>(response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::google::protobuf::Message& GraphService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::graphproto::GraphRequest::default_instance();
    case 1:
      return ::graphproto::GraphRequest::default_instance();
    case 2:
      return ::graphproto::GraphRequest::default_instance();
    case 3:
      return ::graphproto::GraphRequest::default_instance();
    case 4:
      return ::graphproto::GraphRequest::default_instance();
    case 5:
      return ::graphproto::GraphRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
  }
}

const ::google::protobuf::Message& GraphService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::graphproto::GraphResponse::default_instance();
    case 1:
      return ::graphproto::GraphResponse::default_instance();
    case 2:
      return ::graphproto::GraphResponse::default_instance();
    case 3:
      return ::graphproto::GraphResponse::default_instance();
    case 4:
      return ::graphproto::GraphResponse::default_instance();
    case 5:
      return ::graphproto::GraphResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
  }
}

GraphService_Stub::GraphService_Stub(::google::protobuf::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
GraphService_Stub::GraphService_Stub(
    ::google::protobuf::RpcChannel* channel,
    ::google::protobuf::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::google::protobuf::Service::STUB_OWNS_CHANNEL) {}
GraphService_Stub::~GraphService_Stub() {
  if (owns_channel_) delete channel_;
}

void GraphService_Stub::add_graph(::google::protobuf::RpcController* controller,
                              const ::graphproto::GraphRequest* request,
                              ::graphproto::GraphResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}
void GraphService_Stub::add_vertex(::google::protobuf::RpcController* controller,
                              const ::graphproto::GraphRequest* request,
                              ::graphproto::GraphResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(1),
                       controller, request, response, done);
}
void GraphService_Stub::add_edge(::google::protobuf::RpcController* controller,
                              const ::graphproto::GraphRequest* request,
                              ::graphproto::GraphResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(2),
                       controller, request, response, done);
}
void GraphService_Stub::delete_graph(::google::protobuf::RpcController* controller,
                              const ::graphproto::GraphRequest* request,
                              ::graphproto::GraphResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(3),
                       controller, request, response, done);
}
void GraphService_Stub::delete_vertex(::google::protobuf::RpcController* controller,
                              const ::graphproto::GraphRequest* request,
                              ::graphproto::GraphResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(4),
                       controller, request, response, done);
}
void GraphService_Stub::delete_edge(::google::protobuf::RpcController* controller,
                              const ::graphproto::GraphRequest* request,
                              ::graphproto::GraphResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(5),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)

}  // namespace graphproto

// @@protoc_insertion_point(global_scope)
