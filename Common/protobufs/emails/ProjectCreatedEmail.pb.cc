// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProjectCreatedEmail.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProjectCreatedEmail.pb.h"

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
namespace Emails {

namespace {

const ::google::protobuf::Descriptor* ProjectCreatedEmail_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ProjectCreatedEmail_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProjectCreatedEmail_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_ProjectCreatedEmail_2eproto() {
  protobuf_AddDesc_ProjectCreatedEmail_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProjectCreatedEmail.proto");
  GOOGLE_CHECK(file != NULL);
  ProjectCreatedEmail_descriptor_ = file->message_type(0);
  static const int ProjectCreatedEmail_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectCreatedEmail, email_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectCreatedEmail, recipient_email_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectCreatedEmail, project_id_),
  };
  ProjectCreatedEmail_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      ProjectCreatedEmail_descriptor_,
      ProjectCreatedEmail::default_instance_,
      ProjectCreatedEmail_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectCreatedEmail, _has_bits_[0]),
      -1,
      -1,
      sizeof(ProjectCreatedEmail),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectCreatedEmail, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProjectCreatedEmail_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      ProjectCreatedEmail_descriptor_, &ProjectCreatedEmail::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ProjectCreatedEmail_2eproto() {
  delete ProjectCreatedEmail::default_instance_;
  delete ProjectCreatedEmail_reflection_;
}

void protobuf_AddDesc_ProjectCreatedEmail_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_ProjectCreatedEmail_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::SolasMatch::Common::Protobufs::Emails::protobuf_AddDesc_EmailMessage_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031ProjectCreatedEmail.proto\022\"SolasMatch."
    "Common.Protobufs.Emails\032\022EmailMessage.pr"
    "oto\"\235\001\n\023ProjectCreatedEmail\022Y\n\nemail_typ"
    "e\030\001 \002(\01625.SolasMatch.Common.Protobufs.Em"
    "ails.EmailMessage.Type:\016ProjectCreated\022\027"
    "\n\017recipient_email\030\002 \002(\t\022\022\n\nproject_id\030\003 "
    "\002(\005", 243);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProjectCreatedEmail.proto", &protobuf_RegisterTypes);
  ProjectCreatedEmail::default_instance_ = new ProjectCreatedEmail();
  ProjectCreatedEmail::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProjectCreatedEmail_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProjectCreatedEmail_2eproto {
  StaticDescriptorInitializer_ProjectCreatedEmail_2eproto() {
    protobuf_AddDesc_ProjectCreatedEmail_2eproto();
  }
} static_descriptor_initializer_ProjectCreatedEmail_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ProjectCreatedEmail::kEmailTypeFieldNumber;
const int ProjectCreatedEmail::kRecipientEmailFieldNumber;
const int ProjectCreatedEmail::kProjectIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ProjectCreatedEmail::ProjectCreatedEmail()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
}

void ProjectCreatedEmail::InitAsDefaultInstance() {
}

ProjectCreatedEmail::ProjectCreatedEmail(const ProjectCreatedEmail& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
}

void ProjectCreatedEmail::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  email_type_ = 26;
  recipient_email_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  project_id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ProjectCreatedEmail::~ProjectCreatedEmail() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  SharedDtor();
}

void ProjectCreatedEmail::SharedDtor() {
  recipient_email_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void ProjectCreatedEmail::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ProjectCreatedEmail::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ProjectCreatedEmail_descriptor_;
}

const ProjectCreatedEmail& ProjectCreatedEmail::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProjectCreatedEmail_2eproto();
  return *default_instance_;
}

ProjectCreatedEmail* ProjectCreatedEmail::default_instance_ = NULL;

ProjectCreatedEmail* ProjectCreatedEmail::New(::google::protobuf::Arena* arena) const {
  ProjectCreatedEmail* n = new ProjectCreatedEmail;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ProjectCreatedEmail::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  if (_has_bits_[0 / 32] & 7u) {
    email_type_ = 26;
    if (has_recipient_email()) {
      recipient_email_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    project_id_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool ProjectCreatedEmail::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
      case 1: {
        if (tag == 8) {
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
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_recipient_email;
        break;
      }

      // required string recipient_email = 2;
      case 2: {
        if (tag == 18) {
         parse_recipient_email:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_recipient_email()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->recipient_email().data(), this->recipient_email().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_project_id;
        break;
      }

      // required int32 project_id = 3;
      case 3: {
        if (tag == 24) {
         parse_project_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &project_id_)));
          set_has_project_id();
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
  // @@protoc_insertion_point(parse_success:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  return false;
#undef DO_
}

void ProjectCreatedEmail::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
  if (has_email_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->email_type(), output);
  }

  // required string recipient_email = 2;
  if (has_recipient_email()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->recipient_email().data(), this->recipient_email().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->recipient_email(), output);
  }

  // required int32 project_id = 3;
  if (has_project_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->project_id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
}

::google::protobuf::uint8* ProjectCreatedEmail::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
  if (has_email_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->email_type(), target);
  }

  // required string recipient_email = 2;
  if (has_recipient_email()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->recipient_email().data(), this->recipient_email().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->recipient_email(), target);
  }

  // required int32 project_id = 3;
  if (has_project_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->project_id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  return target;
}

int ProjectCreatedEmail::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  int total_size = 0;

  if (has_email_type()) {
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->email_type());
  }

  if (has_recipient_email()) {
    // required string recipient_email = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->recipient_email());
  }

  if (has_project_id()) {
    // required int32 project_id = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->project_id());
  }

  return total_size;
}
int ProjectCreatedEmail::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->email_type());

    // required string recipient_email = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->recipient_email());

    // required int32 project_id = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->project_id());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
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

void ProjectCreatedEmail::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const ProjectCreatedEmail* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const ProjectCreatedEmail>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
    MergeFrom(*source);
  }
}

void ProjectCreatedEmail::MergeFrom(const ProjectCreatedEmail& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_email_type()) {
      set_email_type(from.email_type());
    }
    if (from.has_recipient_email()) {
      set_has_recipient_email();
      recipient_email_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.recipient_email_);
    }
    if (from.has_project_id()) {
      set_project_id(from.project_id());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void ProjectCreatedEmail::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ProjectCreatedEmail::CopyFrom(const ProjectCreatedEmail& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProjectCreatedEmail::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void ProjectCreatedEmail::Swap(ProjectCreatedEmail* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ProjectCreatedEmail::InternalSwap(ProjectCreatedEmail* other) {
  std::swap(email_type_, other->email_type_);
  recipient_email_.Swap(&other->recipient_email_);
  std::swap(project_id_, other->project_id_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ProjectCreatedEmail::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ProjectCreatedEmail_descriptor_;
  metadata.reflection = ProjectCreatedEmail_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ProjectCreatedEmail

// required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
bool ProjectCreatedEmail::has_email_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ProjectCreatedEmail::set_has_email_type() {
  _has_bits_[0] |= 0x00000001u;
}
void ProjectCreatedEmail::clear_has_email_type() {
  _has_bits_[0] &= ~0x00000001u;
}
void ProjectCreatedEmail::clear_email_type() {
  email_type_ = 26;
  clear_has_email_type();
}
 ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type ProjectCreatedEmail::email_type() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.email_type)
  return static_cast< ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type >(email_type_);
}
 void ProjectCreatedEmail::set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value) {
  assert(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type_IsValid(value));
  set_has_email_type();
  email_type_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.email_type)
}

// required string recipient_email = 2;
bool ProjectCreatedEmail::has_recipient_email() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void ProjectCreatedEmail::set_has_recipient_email() {
  _has_bits_[0] |= 0x00000002u;
}
void ProjectCreatedEmail::clear_has_recipient_email() {
  _has_bits_[0] &= ~0x00000002u;
}
void ProjectCreatedEmail::clear_recipient_email() {
  recipient_email_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_recipient_email();
}
 const ::std::string& ProjectCreatedEmail::recipient_email() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
  return recipient_email_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ProjectCreatedEmail::set_recipient_email(const ::std::string& value) {
  set_has_recipient_email();
  recipient_email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}
 void ProjectCreatedEmail::set_recipient_email(const char* value) {
  set_has_recipient_email();
  recipient_email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}
 void ProjectCreatedEmail::set_recipient_email(const char* value, size_t size) {
  set_has_recipient_email();
  recipient_email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}
 ::std::string* ProjectCreatedEmail::mutable_recipient_email() {
  set_has_recipient_email();
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
  return recipient_email_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* ProjectCreatedEmail::release_recipient_email() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
  clear_has_recipient_email();
  return recipient_email_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ProjectCreatedEmail::set_allocated_recipient_email(::std::string* recipient_email) {
  if (recipient_email != NULL) {
    set_has_recipient_email();
  } else {
    clear_has_recipient_email();
  }
  recipient_email_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), recipient_email);
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}

// required int32 project_id = 3;
bool ProjectCreatedEmail::has_project_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void ProjectCreatedEmail::set_has_project_id() {
  _has_bits_[0] |= 0x00000004u;
}
void ProjectCreatedEmail::clear_has_project_id() {
  _has_bits_[0] &= ~0x00000004u;
}
void ProjectCreatedEmail::clear_project_id() {
  project_id_ = 0;
  clear_has_project_id();
}
 ::google::protobuf::int32 ProjectCreatedEmail::project_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.project_id)
  return project_id_;
}
 void ProjectCreatedEmail::set_project_id(::google::protobuf::int32 value) {
  set_has_project_id();
  project_id_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.project_id)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)
