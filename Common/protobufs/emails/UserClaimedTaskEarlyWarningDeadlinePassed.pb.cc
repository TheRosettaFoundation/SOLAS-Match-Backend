// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserClaimedTaskEarlyWarningDeadlinePassed.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "UserClaimedTaskEarlyWarningDeadlinePassed.pb.h"

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

namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {

namespace {

const ::google::protobuf::Descriptor* UserClaimedTaskEarlyWarningDeadlinePassed_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  UserClaimedTaskEarlyWarningDeadlinePassed_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto() {
  protobuf_AddDesc_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "UserClaimedTaskEarlyWarningDeadlinePassed.proto");
  GOOGLE_CHECK(file != NULL);
  UserClaimedTaskEarlyWarningDeadlinePassed_descriptor_ = file->message_type(0);
  static const int UserClaimedTaskEarlyWarningDeadlinePassed_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserClaimedTaskEarlyWarningDeadlinePassed, email_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserClaimedTaskEarlyWarningDeadlinePassed, task_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserClaimedTaskEarlyWarningDeadlinePassed, translator_id_),
  };
  UserClaimedTaskEarlyWarningDeadlinePassed_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      UserClaimedTaskEarlyWarningDeadlinePassed_descriptor_,
      UserClaimedTaskEarlyWarningDeadlinePassed::default_instance_,
      UserClaimedTaskEarlyWarningDeadlinePassed_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserClaimedTaskEarlyWarningDeadlinePassed, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(UserClaimedTaskEarlyWarningDeadlinePassed, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(UserClaimedTaskEarlyWarningDeadlinePassed));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    UserClaimedTaskEarlyWarningDeadlinePassed_descriptor_, &UserClaimedTaskEarlyWarningDeadlinePassed::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto() {
  delete UserClaimedTaskEarlyWarningDeadlinePassed::default_instance_;
  delete UserClaimedTaskEarlyWarningDeadlinePassed_reflection_;
}

void protobuf_AddDesc_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::SolasMatch::Common::Protobufs::Emails::protobuf_AddDesc_EmailMessage_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n/UserClaimedTaskEarlyWarningDeadlinePas"
    "sed.proto\022\"SolasMatch.Common.Protobufs.E"
    "mails\032\022EmailMessage.proto\"\311\001\n)UserClaime"
    "dTaskEarlyWarningDeadlinePassed\022t\n\nemail"
    "_type\030\001 \002(\01625.SolasMatch.Common.Protobuf"
    "s.Emails.EmailMessage.Type:)UserClaimedT"
    "askEarlyWarningDeadlinePassed\022\017\n\007task_id"
    "\030\002 \002(\005\022\025\n\rtranslator_id\030\003 \002(\005", 309);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "UserClaimedTaskEarlyWarningDeadlinePassed.proto", &protobuf_RegisterTypes);
  UserClaimedTaskEarlyWarningDeadlinePassed::default_instance_ = new UserClaimedTaskEarlyWarningDeadlinePassed();
  UserClaimedTaskEarlyWarningDeadlinePassed::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto {
  StaticDescriptorInitializer_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto() {
    protobuf_AddDesc_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto();
  }
} static_descriptor_initializer_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int UserClaimedTaskEarlyWarningDeadlinePassed::kEmailTypeFieldNumber;
const int UserClaimedTaskEarlyWarningDeadlinePassed::kTaskIdFieldNumber;
const int UserClaimedTaskEarlyWarningDeadlinePassed::kTranslatorIdFieldNumber;
#endif  // !_MSC_VER

UserClaimedTaskEarlyWarningDeadlinePassed::UserClaimedTaskEarlyWarningDeadlinePassed()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void UserClaimedTaskEarlyWarningDeadlinePassed::InitAsDefaultInstance() {
}

UserClaimedTaskEarlyWarningDeadlinePassed::UserClaimedTaskEarlyWarningDeadlinePassed(const UserClaimedTaskEarlyWarningDeadlinePassed& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void UserClaimedTaskEarlyWarningDeadlinePassed::SharedCtor() {
  _cached_size_ = 0;
  email_type_ = 33;
  task_id_ = 0;
  translator_id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

UserClaimedTaskEarlyWarningDeadlinePassed::~UserClaimedTaskEarlyWarningDeadlinePassed() {
  SharedDtor();
}

void UserClaimedTaskEarlyWarningDeadlinePassed::SharedDtor() {
  if (this != default_instance_) {
  }
}

void UserClaimedTaskEarlyWarningDeadlinePassed::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* UserClaimedTaskEarlyWarningDeadlinePassed::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return UserClaimedTaskEarlyWarningDeadlinePassed_descriptor_;
}

const UserClaimedTaskEarlyWarningDeadlinePassed& UserClaimedTaskEarlyWarningDeadlinePassed::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto();
  return *default_instance_;
}

UserClaimedTaskEarlyWarningDeadlinePassed* UserClaimedTaskEarlyWarningDeadlinePassed::default_instance_ = NULL;

UserClaimedTaskEarlyWarningDeadlinePassed* UserClaimedTaskEarlyWarningDeadlinePassed::New() const {
  return new UserClaimedTaskEarlyWarningDeadlinePassed;
}

void UserClaimedTaskEarlyWarningDeadlinePassed::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    email_type_ = 33;
    task_id_ = 0;
    translator_id_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool UserClaimedTaskEarlyWarningDeadlinePassed::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserClaimedTaskEarlyWarningDeadlinePassed];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type_IsValid(value)) {
            set_email_type(static_cast< ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_task_id;
        break;
      }

      // required int32 task_id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_task_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &task_id_)));
          set_has_task_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_translator_id;
        break;
      }

      // required int32 translator_id = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_translator_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &translator_id_)));
          set_has_translator_id();
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

void UserClaimedTaskEarlyWarningDeadlinePassed::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserClaimedTaskEarlyWarningDeadlinePassed];
  if (has_email_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->email_type(), output);
  }

  // required int32 task_id = 2;
  if (has_task_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->task_id(), output);
  }

  // required int32 translator_id = 3;
  if (has_translator_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->translator_id(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* UserClaimedTaskEarlyWarningDeadlinePassed::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserClaimedTaskEarlyWarningDeadlinePassed];
  if (has_email_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->email_type(), target);
  }

  // required int32 task_id = 2;
  if (has_task_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->task_id(), target);
  }

  // required int32 translator_id = 3;
  if (has_translator_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->translator_id(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int UserClaimedTaskEarlyWarningDeadlinePassed::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserClaimedTaskEarlyWarningDeadlinePassed];
    if (has_email_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->email_type());
    }

    // required int32 task_id = 2;
    if (has_task_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->task_id());
    }

    // required int32 translator_id = 3;
    if (has_translator_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->translator_id());
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

void UserClaimedTaskEarlyWarningDeadlinePassed::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const UserClaimedTaskEarlyWarningDeadlinePassed* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const UserClaimedTaskEarlyWarningDeadlinePassed*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void UserClaimedTaskEarlyWarningDeadlinePassed::MergeFrom(const UserClaimedTaskEarlyWarningDeadlinePassed& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_email_type()) {
      set_email_type(from.email_type());
    }
    if (from.has_task_id()) {
      set_task_id(from.task_id());
    }
    if (from.has_translator_id()) {
      set_translator_id(from.translator_id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void UserClaimedTaskEarlyWarningDeadlinePassed::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void UserClaimedTaskEarlyWarningDeadlinePassed::CopyFrom(const UserClaimedTaskEarlyWarningDeadlinePassed& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserClaimedTaskEarlyWarningDeadlinePassed::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void UserClaimedTaskEarlyWarningDeadlinePassed::Swap(UserClaimedTaskEarlyWarningDeadlinePassed* other) {
  if (other != this) {
    std::swap(email_type_, other->email_type_);
    std::swap(task_id_, other->task_id_);
    std::swap(translator_id_, other->translator_id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata UserClaimedTaskEarlyWarningDeadlinePassed::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = UserClaimedTaskEarlyWarningDeadlinePassed_descriptor_;
  metadata.reflection = UserClaimedTaskEarlyWarningDeadlinePassed_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)
