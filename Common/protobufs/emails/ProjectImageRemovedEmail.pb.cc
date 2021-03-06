// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProjectImageRemovedEmail.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProjectImageRemovedEmail.pb.h"

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

const ::google::protobuf::Descriptor* ProjectImageRemovedEmail_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ProjectImageRemovedEmail_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProjectImageRemovedEmail_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_ProjectImageRemovedEmail_2eproto() {
  protobuf_AddDesc_ProjectImageRemovedEmail_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProjectImageRemovedEmail.proto");
  GOOGLE_CHECK(file != NULL);
  ProjectImageRemovedEmail_descriptor_ = file->message_type(0);
  static const int ProjectImageRemovedEmail_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectImageRemovedEmail, email_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectImageRemovedEmail, project_id_),
  };
  ProjectImageRemovedEmail_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      ProjectImageRemovedEmail_descriptor_,
      ProjectImageRemovedEmail::default_instance_,
      ProjectImageRemovedEmail_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectImageRemovedEmail, _has_bits_[0]),
      -1,
      -1,
      sizeof(ProjectImageRemovedEmail),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProjectImageRemovedEmail, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProjectImageRemovedEmail_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      ProjectImageRemovedEmail_descriptor_, &ProjectImageRemovedEmail::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ProjectImageRemovedEmail_2eproto() {
  delete ProjectImageRemovedEmail::default_instance_;
  delete ProjectImageRemovedEmail_reflection_;
}

void protobuf_AddDesc_ProjectImageRemovedEmail_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_ProjectImageRemovedEmail_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::SolasMatch::Common::Protobufs::Emails::protobuf_AddDesc_EmailMessage_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\036ProjectImageRemovedEmail.proto\022\"SolasM"
    "atch.Common.Protobufs.Emails\032\022EmailMessa"
    "ge.proto\"\223\001\n\030ProjectImageRemovedEmail\022c\n"
    "\nemail_type\030\001 \002(\01625.SolasMatch.Common.Pr"
    "otobufs.Emails.EmailMessage.Type:\030Projec"
    "tImageRemovedEmail\022\022\n\nproject_id\030\002 \002(\005", 238);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProjectImageRemovedEmail.proto", &protobuf_RegisterTypes);
  ProjectImageRemovedEmail::default_instance_ = new ProjectImageRemovedEmail();
  ProjectImageRemovedEmail::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProjectImageRemovedEmail_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProjectImageRemovedEmail_2eproto {
  StaticDescriptorInitializer_ProjectImageRemovedEmail_2eproto() {
    protobuf_AddDesc_ProjectImageRemovedEmail_2eproto();
  }
} static_descriptor_initializer_ProjectImageRemovedEmail_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ProjectImageRemovedEmail::kEmailTypeFieldNumber;
const int ProjectImageRemovedEmail::kProjectIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ProjectImageRemovedEmail::ProjectImageRemovedEmail()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
}

void ProjectImageRemovedEmail::InitAsDefaultInstance() {
}

ProjectImageRemovedEmail::ProjectImageRemovedEmail(const ProjectImageRemovedEmail& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
}

void ProjectImageRemovedEmail::SharedCtor() {
  _cached_size_ = 0;
  email_type_ = 30;
  project_id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ProjectImageRemovedEmail::~ProjectImageRemovedEmail() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  SharedDtor();
}

void ProjectImageRemovedEmail::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ProjectImageRemovedEmail::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ProjectImageRemovedEmail::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ProjectImageRemovedEmail_descriptor_;
}

const ProjectImageRemovedEmail& ProjectImageRemovedEmail::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProjectImageRemovedEmail_2eproto();
  return *default_instance_;
}

ProjectImageRemovedEmail* ProjectImageRemovedEmail::default_instance_ = NULL;

ProjectImageRemovedEmail* ProjectImageRemovedEmail::New(::google::protobuf::Arena* arena) const {
  ProjectImageRemovedEmail* n = new ProjectImageRemovedEmail;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ProjectImageRemovedEmail::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  if (_has_bits_[0 / 32] & 3u) {
    email_type_ = 30;
    project_id_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool ProjectImageRemovedEmail::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectImageRemovedEmail];
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
        if (input->ExpectTag(16)) goto parse_project_id;
        break;
      }

      // required int32 project_id = 2;
      case 2: {
        if (tag == 16) {
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
  // @@protoc_insertion_point(parse_success:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  return false;
#undef DO_
}

void ProjectImageRemovedEmail::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectImageRemovedEmail];
  if (has_email_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->email_type(), output);
  }

  // required int32 project_id = 2;
  if (has_project_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->project_id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
}

::google::protobuf::uint8* ProjectImageRemovedEmail::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectImageRemovedEmail];
  if (has_email_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->email_type(), target);
  }

  // required int32 project_id = 2;
  if (has_project_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->project_id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  return target;
}

int ProjectImageRemovedEmail::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  int total_size = 0;

  if (has_email_type()) {
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectImageRemovedEmail];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->email_type());
  }

  if (has_project_id()) {
    // required int32 project_id = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->project_id());
  }

  return total_size;
}
int ProjectImageRemovedEmail::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectImageRemovedEmail];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->email_type());

    // required int32 project_id = 2;
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

void ProjectImageRemovedEmail::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const ProjectImageRemovedEmail* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const ProjectImageRemovedEmail>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
    MergeFrom(*source);
  }
}

void ProjectImageRemovedEmail::MergeFrom(const ProjectImageRemovedEmail& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_email_type()) {
      set_email_type(from.email_type());
    }
    if (from.has_project_id()) {
      set_project_id(from.project_id());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void ProjectImageRemovedEmail::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ProjectImageRemovedEmail::CopyFrom(const ProjectImageRemovedEmail& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProjectImageRemovedEmail::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void ProjectImageRemovedEmail::Swap(ProjectImageRemovedEmail* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ProjectImageRemovedEmail::InternalSwap(ProjectImageRemovedEmail* other) {
  std::swap(email_type_, other->email_type_);
  std::swap(project_id_, other->project_id_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ProjectImageRemovedEmail::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ProjectImageRemovedEmail_descriptor_;
  metadata.reflection = ProjectImageRemovedEmail_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ProjectImageRemovedEmail

// required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectImageRemovedEmail];
bool ProjectImageRemovedEmail::has_email_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ProjectImageRemovedEmail::set_has_email_type() {
  _has_bits_[0] |= 0x00000001u;
}
void ProjectImageRemovedEmail::clear_has_email_type() {
  _has_bits_[0] &= ~0x00000001u;
}
void ProjectImageRemovedEmail::clear_email_type() {
  email_type_ = 30;
  clear_has_email_type();
}
 ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type ProjectImageRemovedEmail::email_type() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail.email_type)
  return static_cast< ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type >(email_type_);
}
 void ProjectImageRemovedEmail::set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value) {
  assert(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type_IsValid(value));
  set_has_email_type();
  email_type_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail.email_type)
}

// required int32 project_id = 2;
bool ProjectImageRemovedEmail::has_project_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void ProjectImageRemovedEmail::set_has_project_id() {
  _has_bits_[0] |= 0x00000002u;
}
void ProjectImageRemovedEmail::clear_has_project_id() {
  _has_bits_[0] &= ~0x00000002u;
}
void ProjectImageRemovedEmail::clear_project_id() {
  project_id_ = 0;
  clear_has_project_id();
}
 ::google::protobuf::int32 ProjectImageRemovedEmail::project_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail.project_id)
  return project_id_;
}
 void ProjectImageRemovedEmail::set_project_id(::google::protobuf::int32 value) {
  set_has_project_id();
  project_id_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectImageRemovedEmail.project_id)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)
