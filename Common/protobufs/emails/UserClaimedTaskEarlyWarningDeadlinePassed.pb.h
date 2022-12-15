// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserClaimedTaskEarlyWarningDeadlinePassed.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "EmailMessage.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto;
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {
class UserClaimedTaskEarlyWarningDeadlinePassed;
class UserClaimedTaskEarlyWarningDeadlinePassedDefaultTypeInternal;
extern UserClaimedTaskEarlyWarningDeadlinePassedDefaultTypeInternal _UserClaimedTaskEarlyWarningDeadlinePassed_default_instance_;
}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> ::SolasMatch::Common::Protobufs::Emails::UserClaimedTaskEarlyWarningDeadlinePassed* Arena::CreateMaybeMessage<::SolasMatch::Common::Protobufs::Emails::UserClaimedTaskEarlyWarningDeadlinePassed>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Emails {

// ===================================================================

class UserClaimedTaskEarlyWarningDeadlinePassed PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed) */ {
 public:
  inline UserClaimedTaskEarlyWarningDeadlinePassed() : UserClaimedTaskEarlyWarningDeadlinePassed(nullptr) {};
  virtual ~UserClaimedTaskEarlyWarningDeadlinePassed();

  UserClaimedTaskEarlyWarningDeadlinePassed(const UserClaimedTaskEarlyWarningDeadlinePassed& from);
  UserClaimedTaskEarlyWarningDeadlinePassed(UserClaimedTaskEarlyWarningDeadlinePassed&& from) noexcept
    : UserClaimedTaskEarlyWarningDeadlinePassed() {
    *this = ::std::move(from);
  }

  inline UserClaimedTaskEarlyWarningDeadlinePassed& operator=(const UserClaimedTaskEarlyWarningDeadlinePassed& from) {
    CopyFrom(from);
    return *this;
  }
  inline UserClaimedTaskEarlyWarningDeadlinePassed& operator=(UserClaimedTaskEarlyWarningDeadlinePassed&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const UserClaimedTaskEarlyWarningDeadlinePassed& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const UserClaimedTaskEarlyWarningDeadlinePassed* internal_default_instance() {
    return reinterpret_cast<const UserClaimedTaskEarlyWarningDeadlinePassed*>(
               &_UserClaimedTaskEarlyWarningDeadlinePassed_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(UserClaimedTaskEarlyWarningDeadlinePassed& a, UserClaimedTaskEarlyWarningDeadlinePassed& b) {
    a.Swap(&b);
  }
  inline void Swap(UserClaimedTaskEarlyWarningDeadlinePassed* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(UserClaimedTaskEarlyWarningDeadlinePassed* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline UserClaimedTaskEarlyWarningDeadlinePassed* New() const final {
    return CreateMaybeMessage<UserClaimedTaskEarlyWarningDeadlinePassed>(nullptr);
  }

  UserClaimedTaskEarlyWarningDeadlinePassed* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<UserClaimedTaskEarlyWarningDeadlinePassed>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const UserClaimedTaskEarlyWarningDeadlinePassed& from);
  void MergeFrom(const UserClaimedTaskEarlyWarningDeadlinePassed& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(UserClaimedTaskEarlyWarningDeadlinePassed* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed";
  }
  protected:
  explicit UserClaimedTaskEarlyWarningDeadlinePassed(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto);
    return ::descriptor_table_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTaskIdFieldNumber = 2,
    kTranslatorIdFieldNumber = 3,
    kEmailTypeFieldNumber = 1,
  };
  // required int32 task_id = 2;
  bool has_task_id() const;
  private:
  bool _internal_has_task_id() const;
  public:
  void clear_task_id();
  ::PROTOBUF_NAMESPACE_ID::int32 task_id() const;
  void set_task_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_task_id() const;
  void _internal_set_task_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // required int32 translator_id = 3;
  bool has_translator_id() const;
  private:
  bool _internal_has_translator_id() const;
  public:
  void clear_translator_id();
  ::PROTOBUF_NAMESPACE_ID::int32 translator_id() const;
  void set_translator_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_translator_id() const;
  void _internal_set_translator_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserClaimedTaskEarlyWarningDeadlinePassed];
  bool has_email_type() const;
  private:
  bool _internal_has_email_type() const;
  public:
  void clear_email_type();
  ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type email_type() const;
  void set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value);
  private:
  ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type _internal_email_type() const;
  void _internal_set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value);
  public:

  // @@protoc_insertion_point(class_scope:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 task_id_;
  ::PROTOBUF_NAMESPACE_ID::int32 translator_id_;
  int email_type_;
  friend struct ::TableStruct_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// UserClaimedTaskEarlyWarningDeadlinePassed

// required .SolasMatch.Common.Protobufs.Emails.EmailMessage.Type email_type = 1 [default = UserClaimedTaskEarlyWarningDeadlinePassed];
inline bool UserClaimedTaskEarlyWarningDeadlinePassed::_internal_has_email_type() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool UserClaimedTaskEarlyWarningDeadlinePassed::has_email_type() const {
  return _internal_has_email_type();
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::clear_email_type() {
  email_type_ = 33;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type UserClaimedTaskEarlyWarningDeadlinePassed::_internal_email_type() const {
  return static_cast< ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type >(email_type_);
}
inline ::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type UserClaimedTaskEarlyWarningDeadlinePassed::email_type() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed.email_type)
  return _internal_email_type();
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::_internal_set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value) {
  assert(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type_IsValid(value));
  _has_bits_[0] |= 0x00000004u;
  email_type_ = value;
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::set_email_type(::SolasMatch::Common::Protobufs::Emails::EmailMessage_Type value) {
  _internal_set_email_type(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed.email_type)
}

// required int32 task_id = 2;
inline bool UserClaimedTaskEarlyWarningDeadlinePassed::_internal_has_task_id() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool UserClaimedTaskEarlyWarningDeadlinePassed::has_task_id() const {
  return _internal_has_task_id();
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::clear_task_id() {
  task_id_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 UserClaimedTaskEarlyWarningDeadlinePassed::_internal_task_id() const {
  return task_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 UserClaimedTaskEarlyWarningDeadlinePassed::task_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed.task_id)
  return _internal_task_id();
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::_internal_set_task_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  task_id_ = value;
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::set_task_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_task_id(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed.task_id)
}

// required int32 translator_id = 3;
inline bool UserClaimedTaskEarlyWarningDeadlinePassed::_internal_has_translator_id() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool UserClaimedTaskEarlyWarningDeadlinePassed::has_translator_id() const {
  return _internal_has_translator_id();
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::clear_translator_id() {
  translator_id_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 UserClaimedTaskEarlyWarningDeadlinePassed::_internal_translator_id() const {
  return translator_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 UserClaimedTaskEarlyWarningDeadlinePassed::translator_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed.translator_id)
  return _internal_translator_id();
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::_internal_set_translator_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  translator_id_ = value;
}
inline void UserClaimedTaskEarlyWarningDeadlinePassed::set_translator_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_translator_id(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Emails.UserClaimedTaskEarlyWarningDeadlinePassed.translator_id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Emails
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_UserClaimedTaskEarlyWarningDeadlinePassed_2eproto
