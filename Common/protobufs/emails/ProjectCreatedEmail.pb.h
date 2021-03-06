// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProjectCreatedEmail.proto

#ifndef PROTOBUF_ProjectCreatedEmail_2eproto__INCLUDED
#define PROTOBUF_ProjectCreatedEmail_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "EmailMessage.pb.h"
// @@protoc_insertion_point(includes)

namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_ProjectCreatedEmail_2eproto();
void protobuf_AssignDesc_ProjectCreatedEmail_2eproto();
void protobuf_ShutdownFile_ProjectCreatedEmail_2eproto();

class ProjectCreatedEmail;

// ===================================================================

class ProjectCreatedEmail : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail) */ {
 public:
  ProjectCreatedEmail();
  virtual ~ProjectCreatedEmail();

  ProjectCreatedEmail(const ProjectCreatedEmail& from);

  inline ProjectCreatedEmail& operator=(const ProjectCreatedEmail& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProjectCreatedEmail& default_instance();

  void Swap(ProjectCreatedEmail* other);

  // implements Message ----------------------------------------------

  inline ProjectCreatedEmail* New() const { return New(NULL); }

  ProjectCreatedEmail* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProjectCreatedEmail& from);
  void MergeFrom(const ProjectCreatedEmail& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ProjectCreatedEmail* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
  bool has_email_type() const;
  void clear_email_type();
  static const int kEmailTypeFieldNumber = 1;
  ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type email_type() const;
  void set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value);

  // required string recipient_email = 2;
  bool has_recipient_email() const;
  void clear_recipient_email();
  static const int kRecipientEmailFieldNumber = 2;
  const ::std::string& recipient_email() const;
  void set_recipient_email(const ::std::string& value);
  void set_recipient_email(const char* value);
  void set_recipient_email(const char* value, size_t size);
  ::std::string* mutable_recipient_email();
  ::std::string* release_recipient_email();
  void set_allocated_recipient_email(::std::string* recipient_email);

  // required int32 project_id = 3;
  bool has_project_id() const;
  void clear_project_id();
  static const int kProjectIdFieldNumber = 3;
  ::google::protobuf::int32 project_id() const;
  void set_project_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail)
 private:
  inline void set_has_email_type();
  inline void clear_has_email_type();
  inline void set_has_recipient_email();
  inline void clear_has_recipient_email();
  inline void set_has_project_id();
  inline void clear_has_project_id();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr recipient_email_;
  int email_type_;
  ::google::protobuf::int32 project_id_;
  friend void  protobuf_AddDesc_ProjectCreatedEmail_2eproto();
  friend void protobuf_AssignDesc_ProjectCreatedEmail_2eproto();
  friend void protobuf_ShutdownFile_ProjectCreatedEmail_2eproto();

  void InitAsDefaultInstance();
  static ProjectCreatedEmail* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ProjectCreatedEmail

// required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = ProjectCreated];
inline bool ProjectCreatedEmail::has_email_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProjectCreatedEmail::set_has_email_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProjectCreatedEmail::clear_has_email_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProjectCreatedEmail::clear_email_type() {
  email_type_ = 26;
  clear_has_email_type();
}
inline ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type ProjectCreatedEmail::email_type() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.email_type)
  return static_cast< ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type >(email_type_);
}
inline void ProjectCreatedEmail::set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value) {
  assert(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type_IsValid(value));
  set_has_email_type();
  email_type_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.email_type)
}

// required string recipient_email = 2;
inline bool ProjectCreatedEmail::has_recipient_email() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProjectCreatedEmail::set_has_recipient_email() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProjectCreatedEmail::clear_has_recipient_email() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProjectCreatedEmail::clear_recipient_email() {
  recipient_email_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_recipient_email();
}
inline const ::std::string& ProjectCreatedEmail::recipient_email() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
  return recipient_email_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ProjectCreatedEmail::set_recipient_email(const ::std::string& value) {
  set_has_recipient_email();
  recipient_email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}
inline void ProjectCreatedEmail::set_recipient_email(const char* value) {
  set_has_recipient_email();
  recipient_email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}
inline void ProjectCreatedEmail::set_recipient_email(const char* value, size_t size) {
  set_has_recipient_email();
  recipient_email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}
inline ::std::string* ProjectCreatedEmail::mutable_recipient_email() {
  set_has_recipient_email();
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
  return recipient_email_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ProjectCreatedEmail::release_recipient_email() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
  clear_has_recipient_email();
  return recipient_email_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ProjectCreatedEmail::set_allocated_recipient_email(::std::string* recipient_email) {
  if (recipient_email != NULL) {
    set_has_recipient_email();
  } else {
    clear_has_recipient_email();
  }
  recipient_email_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), recipient_email);
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.recipient_email)
}

// required int32 project_id = 3;
inline bool ProjectCreatedEmail::has_project_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ProjectCreatedEmail::set_has_project_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ProjectCreatedEmail::clear_has_project_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ProjectCreatedEmail::clear_project_id() {
  project_id_ = 0;
  clear_has_project_id();
}
inline ::google::protobuf::int32 ProjectCreatedEmail::project_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.project_id)
  return project_id_;
}
inline void ProjectCreatedEmail::set_project_id(::google::protobuf::int32 value) {
  set_has_project_id();
  project_id_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.ProjectCreatedEmail.project_id)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProjectCreatedEmail_2eproto__INCLUDED
