// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserTaskScoreRequest.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "UserTaskScoreRequest.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Requests {

namespace {

const ::google::protobuf::Descriptor* UserTaskScoreRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  UserTaskScoreRequest_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_UserTaskScoreRequest_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_UserTaskScoreRequest_2eproto() {
  protobuf_AddDesc_UserTaskScoreRequest_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "UserTaskScoreRequest.proto");
  GOOGLE_CHECK(file != NULL);
  UserTaskScoreRequest_descriptor_ = file->message_type(0);
  static const int UserTaskScoreRequest_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserTaskScoreRequest, class_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserTaskScoreRequest, task_id_),
  };
  UserTaskScoreRequest_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      UserTaskScoreRequest_descriptor_,
      UserTaskScoreRequest::default_instance_,
      UserTaskScoreRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserTaskScoreRequest, _has_bits_[0]),
      -1,
      -1,
      sizeof(UserTaskScoreRequest),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserTaskScoreRequest, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_UserTaskScoreRequest_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      UserTaskScoreRequest_descriptor_, &UserTaskScoreRequest::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_UserTaskScoreRequest_2eproto() {
  delete UserTaskScoreRequest::default_instance_;
  delete UserTaskScoreRequest_reflection_;
  delete UserTaskScoreRequest::_default_class_name_;
}

void protobuf_AddDesc_UserTaskScoreRequest_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_UserTaskScoreRequest_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032UserTaskScoreRequest.proto\022$SolasMatch"
    ".Common.Protobufs.Requests\"Q\n\024UserTaskSc"
    "oreRequest\022(\n\nclass_name\030\001 \002(\t:\024UserTask"
    "ScoreRequest\022\017\n\007task_id\030\002 \001(\005", 149);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "UserTaskScoreRequest.proto", &protobuf_RegisterTypes);
  UserTaskScoreRequest::_default_class_name_ =
      new ::std::string("UserTaskScoreRequest", 20);
  UserTaskScoreRequest::default_instance_ = new UserTaskScoreRequest();
  UserTaskScoreRequest::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_UserTaskScoreRequest_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_UserTaskScoreRequest_2eproto {
  StaticDescriptorInitializer_UserTaskScoreRequest_2eproto() {
    protobuf_AddDesc_UserTaskScoreRequest_2eproto();
  }
} static_descriptor_initializer_UserTaskScoreRequest_2eproto_;

// ===================================================================

::std::string* UserTaskScoreRequest::_default_class_name_ = NULL;
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int UserTaskScoreRequest::kClassNameFieldNumber;
const int UserTaskScoreRequest::kTaskIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

UserTaskScoreRequest::UserTaskScoreRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
}

void UserTaskScoreRequest::InitAsDefaultInstance() {
}

UserTaskScoreRequest::UserTaskScoreRequest(const UserTaskScoreRequest& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
}

void UserTaskScoreRequest::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  class_name_.UnsafeSetDefault(_default_class_name_);
  task_id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

UserTaskScoreRequest::~UserTaskScoreRequest() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  SharedDtor();
}

void UserTaskScoreRequest::SharedDtor() {
  class_name_.DestroyNoArena(_default_class_name_);
  if (this != default_instance_) {
  }
}

void UserTaskScoreRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* UserTaskScoreRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return UserTaskScoreRequest_descriptor_;
}

const UserTaskScoreRequest& UserTaskScoreRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_UserTaskScoreRequest_2eproto();
  return *default_instance_;
}

UserTaskScoreRequest* UserTaskScoreRequest::default_instance_ = NULL;

UserTaskScoreRequest* UserTaskScoreRequest::New(::google::protobuf::Arena* arena) const {
  UserTaskScoreRequest* n = new UserTaskScoreRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void UserTaskScoreRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  if (_has_bits_[0 / 32] & 3u) {
    if (has_class_name()) {
      class_name_.ClearToDefaultNoArena(_default_class_name_);
    }
    task_id_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool UserTaskScoreRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string class_name = 1 [default = "UserTaskScoreRequest"];
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_class_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->class_name().data(), this->class_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_task_id;
        break;
      }

      // optional int32 task_id = 2;
      case 2: {
        if (tag == 16) {
         parse_task_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &task_id_)));
          set_has_task_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  return false;
#undef DO_
}

void UserTaskScoreRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  // required string class_name = 1 [default = "UserTaskScoreRequest"];
  if (has_class_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->class_name().data(), this->class_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->class_name(), output);
  }

  // optional int32 task_id = 2;
  if (has_task_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->task_id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
}

::google::protobuf::uint8* UserTaskScoreRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  // required string class_name = 1 [default = "UserTaskScoreRequest"];
  if (has_class_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->class_name().data(), this->class_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->class_name(), target);
  }

  // optional int32 task_id = 2;
  if (has_task_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->task_id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  return target;
}

int UserTaskScoreRequest::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  int total_size = 0;

  // required string class_name = 1 [default = "UserTaskScoreRequest"];
  if (has_class_name()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->class_name());
  }
  // optional int32 task_id = 2;
  if (has_task_id()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->task_id());
  }

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void UserTaskScoreRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const UserTaskScoreRequest* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const UserTaskScoreRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
    MergeFrom(*source);
  }
}

void UserTaskScoreRequest::MergeFrom(const UserTaskScoreRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_class_name()) {
      set_has_class_name();
      class_name_.AssignWithDefault(_default_class_name_, from.class_name_);
    }
    if (from.has_task_id()) {
      set_task_id(from.task_id());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void UserTaskScoreRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void UserTaskScoreRequest::CopyFrom(const UserTaskScoreRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserTaskScoreRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void UserTaskScoreRequest::Swap(UserTaskScoreRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void UserTaskScoreRequest::InternalSwap(UserTaskScoreRequest* other) {
  class_name_.Swap(&other->class_name_);
  std::swap(task_id_, other->task_id_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata UserTaskScoreRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = UserTaskScoreRequest_descriptor_;
  metadata.reflection = UserTaskScoreRequest_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// UserTaskScoreRequest

// required string class_name = 1 [default = "UserTaskScoreRequest"];
bool UserTaskScoreRequest::has_class_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void UserTaskScoreRequest::set_has_class_name() {
  _has_bits_[0] |= 0x00000001u;
}
void UserTaskScoreRequest::clear_has_class_name() {
  _has_bits_[0] &= ~0x00000001u;
}
void UserTaskScoreRequest::clear_class_name() {
  class_name_.ClearToDefaultNoArena(_default_class_name_);
  clear_has_class_name();
}
 const ::std::string& UserTaskScoreRequest::class_name() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
  return class_name_.GetNoArena(_default_class_name_);
}
 void UserTaskScoreRequest::set_class_name(const ::std::string& value) {
  set_has_class_name();
  class_name_.SetNoArena(_default_class_name_, value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
}
 void UserTaskScoreRequest::set_class_name(const char* value) {
  set_has_class_name();
  class_name_.SetNoArena(_default_class_name_, ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
}
 void UserTaskScoreRequest::set_class_name(const char* value, size_t size) {
  set_has_class_name();
  class_name_.SetNoArena(_default_class_name_,
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
}
 ::std::string* UserTaskScoreRequest::mutable_class_name() {
  set_has_class_name();
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
  return class_name_.MutableNoArena(_default_class_name_);
}
 ::std::string* UserTaskScoreRequest::release_class_name() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
  clear_has_class_name();
  return class_name_.ReleaseNoArena(_default_class_name_);
}
 void UserTaskScoreRequest::set_allocated_class_name(::std::string* class_name) {
  if (class_name != NULL) {
    set_has_class_name();
  } else {
    clear_has_class_name();
  }
  class_name_.SetAllocatedNoArena(_default_class_name_, class_name);
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.class_name)
}

// optional int32 task_id = 2;
bool UserTaskScoreRequest::has_task_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void UserTaskScoreRequest::set_has_task_id() {
  _has_bits_[0] |= 0x00000002u;
}
void UserTaskScoreRequest::clear_has_task_id() {
  _has_bits_[0] &= ~0x00000002u;
}
void UserTaskScoreRequest::clear_task_id() {
  task_id_ = 0;
  clear_has_task_id();
}
 ::google::protobuf::int32 UserTaskScoreRequest::task_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.task_id)
  return task_id_;
}
 void UserTaskScoreRequest::set_task_id(::google::protobuf::int32 value) {
  set_has_task_id();
  task_id_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Requests.UserTaskScoreRequest.task_id)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Requests
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)
