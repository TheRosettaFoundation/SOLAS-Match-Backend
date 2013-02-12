// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "FeedbackEmail.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* FeedbackEmail_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FeedbackEmail_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_FeedbackEmail_2eproto() {
  protobuf_AddDesc_FeedbackEmail_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "FeedbackEmail.proto");
  GOOGLE_CHECK(file != NULL);
  FeedbackEmail_descriptor_ = file->message_type(0);
  static const int FeedbackEmail_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeedbackEmail, email_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeedbackEmail, taskid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeedbackEmail, userid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeedbackEmail, feedback_),
  };
  FeedbackEmail_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FeedbackEmail_descriptor_,
      FeedbackEmail::default_instance_,
      FeedbackEmail_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeedbackEmail, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeedbackEmail, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FeedbackEmail));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_FeedbackEmail_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FeedbackEmail_descriptor_, &FeedbackEmail::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_FeedbackEmail_2eproto() {
  delete FeedbackEmail::default_instance_;
  delete FeedbackEmail_reflection_;
}

void protobuf_AddDesc_FeedbackEmail_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_EmailMessage_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\023FeedbackEmail.proto\032\022EmailMessage.prot"
    "o\"x\n\rFeedbackEmail\0225\n\nemail_type\030\001 \002(\0162\022"
    ".EmailMessage.Type:\rFeedbackEmail\022\016\n\006tas"
    "kId\030\002 \002(\005\022\016\n\006userId\030\003 \003(\005\022\020\n\010feedback\030\004 "
    "\002(\t", 163);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "FeedbackEmail.proto", &protobuf_RegisterTypes);
  FeedbackEmail::default_instance_ = new FeedbackEmail();
  FeedbackEmail::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_FeedbackEmail_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_FeedbackEmail_2eproto {
  StaticDescriptorInitializer_FeedbackEmail_2eproto() {
    protobuf_AddDesc_FeedbackEmail_2eproto();
  }
} static_descriptor_initializer_FeedbackEmail_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int FeedbackEmail::kEmailTypeFieldNumber;
const int FeedbackEmail::kTaskIdFieldNumber;
const int FeedbackEmail::kUserIdFieldNumber;
const int FeedbackEmail::kFeedbackFieldNumber;
#endif  // !_MSC_VER

FeedbackEmail::FeedbackEmail()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FeedbackEmail::InitAsDefaultInstance() {
}

FeedbackEmail::FeedbackEmail(const FeedbackEmail& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FeedbackEmail::SharedCtor() {
  _cached_size_ = 0;
  email_type_ = 11;
  taskid_ = 0;
  feedback_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FeedbackEmail::~FeedbackEmail() {
  SharedDtor();
}

void FeedbackEmail::SharedDtor() {
  if (feedback_ != &::google::protobuf::internal::kEmptyString) {
    delete feedback_;
  }
  if (this != default_instance_) {
  }
}

void FeedbackEmail::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FeedbackEmail::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FeedbackEmail_descriptor_;
}

const FeedbackEmail& FeedbackEmail::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_FeedbackEmail_2eproto();  return *default_instance_;
}

FeedbackEmail* FeedbackEmail::default_instance_ = NULL;

FeedbackEmail* FeedbackEmail::New() const {
  return new FeedbackEmail;
}

void FeedbackEmail::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    email_type_ = 11;
    taskid_ = 0;
    if (has_feedback()) {
      if (feedback_ != &::google::protobuf::internal::kEmptyString) {
        feedback_->clear();
      }
    }
  }
  userid_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FeedbackEmail::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .EmailMessage.Type email_type = 1 [default = FeedbackEmail];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::EmailMessage_Type_IsValid(value)) {
            set_email_type(static_cast< ::EmailMessage_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_taskId;
        break;
      }
      
      // required int32 taskId = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_taskId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &taskid_)));
          set_has_taskid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_userId;
        break;
      }
      
      // repeated int32 userId = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_userId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 24, input, this->mutable_userid())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_userid())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_userId;
        if (input->ExpectTag(34)) goto parse_feedback;
        break;
      }
      
      // required string feedback = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_feedback:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_feedback()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->feedback().data(), this->feedback().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
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

void FeedbackEmail::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .EmailMessage.Type email_type = 1 [default = FeedbackEmail];
  if (has_email_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->email_type(), output);
  }
  
  // required int32 taskId = 2;
  if (has_taskid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->taskid(), output);
  }
  
  // repeated int32 userId = 3;
  for (int i = 0; i < this->userid_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      3, this->userid(i), output);
  }
  
  // required string feedback = 4;
  if (has_feedback()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->feedback().data(), this->feedback().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->feedback(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FeedbackEmail::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .EmailMessage.Type email_type = 1 [default = FeedbackEmail];
  if (has_email_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->email_type(), target);
  }
  
  // required int32 taskId = 2;
  if (has_taskid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->taskid(), target);
  }
  
  // repeated int32 userId = 3;
  for (int i = 0; i < this->userid_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(3, this->userid(i), target);
  }
  
  // required string feedback = 4;
  if (has_feedback()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->feedback().data(), this->feedback().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->feedback(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FeedbackEmail::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .EmailMessage.Type email_type = 1 [default = FeedbackEmail];
    if (has_email_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->email_type());
    }
    
    // required int32 taskId = 2;
    if (has_taskid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->taskid());
    }
    
    // required string feedback = 4;
    if (has_feedback()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->feedback());
    }
    
  }
  // repeated int32 userId = 3;
  {
    int data_size = 0;
    for (int i = 0; i < this->userid_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->userid(i));
    }
    total_size += 1 * this->userid_size() + data_size;
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

void FeedbackEmail::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FeedbackEmail* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FeedbackEmail*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FeedbackEmail::MergeFrom(const FeedbackEmail& from) {
  GOOGLE_CHECK_NE(&from, this);
  userid_.MergeFrom(from.userid_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_email_type()) {
      set_email_type(from.email_type());
    }
    if (from.has_taskid()) {
      set_taskid(from.taskid());
    }
    if (from.has_feedback()) {
      set_feedback(from.feedback());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FeedbackEmail::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FeedbackEmail::CopyFrom(const FeedbackEmail& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FeedbackEmail::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000b) != 0x0000000b) return false;
  
  return true;
}

void FeedbackEmail::Swap(FeedbackEmail* other) {
  if (other != this) {
    std::swap(email_type_, other->email_type_);
    std::swap(taskid_, other->taskid_);
    userid_.Swap(&other->userid_);
    std::swap(feedback_, other->feedback_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FeedbackEmail::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FeedbackEmail_descriptor_;
  metadata.reflection = FeedbackEmail_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
