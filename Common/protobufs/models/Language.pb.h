// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Language.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Language_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Language_2eproto

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
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Language_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Language_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Language_2eproto;
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {
class Language;
class LanguageDefaultTypeInternal;
extern LanguageDefaultTypeInternal _Language_default_instance_;
}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> ::SolasMatch::Common::Protobufs::Models::Language* Arena::CreateMaybeMessage<::SolasMatch::Common::Protobufs::Models::Language>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {

// ===================================================================

class Language PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SolasMatch.Common.Protobufs.Models.Language) */ {
 public:
  inline Language() : Language(nullptr) {};
  virtual ~Language();

  Language(const Language& from);
  Language(Language&& from) noexcept
    : Language() {
    *this = ::std::move(from);
  }

  inline Language& operator=(const Language& from) {
    CopyFrom(from);
    return *this;
  }
  inline Language& operator=(Language&& from) noexcept {
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
  static const Language& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Language* internal_default_instance() {
    return reinterpret_cast<const Language*>(
               &_Language_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Language& a, Language& b) {
    a.Swap(&b);
  }
  inline void Swap(Language* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Language* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Language* New() const final {
    return CreateMaybeMessage<Language>(nullptr);
  }

  Language* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Language>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Language& from);
  void MergeFrom(const Language& from);
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
  void InternalSwap(Language* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SolasMatch.Common.Protobufs.Models.Language";
  }
  protected:
  explicit Language(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Language_2eproto);
    return ::descriptor_table_Language_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCodeFieldNumber = 2,
    kNameFieldNumber = 3,
    kIdFieldNumber = 1,
  };
  // optional string code = 2;
  bool has_code() const;
  private:
  bool _internal_has_code() const;
  public:
  void clear_code();
  const std::string& code() const;
  void set_code(const std::string& value);
  void set_code(std::string&& value);
  void set_code(const char* value);
  void set_code(const char* value, size_t size);
  std::string* mutable_code();
  std::string* release_code();
  void set_allocated_code(std::string* code);
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  std::string* unsafe_arena_release_code();
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_code(
      std::string* code);
  private:
  const std::string& _internal_code() const;
  void _internal_set_code(const std::string& value);
  std::string* _internal_mutable_code();
  public:

  // optional string name = 3;
  bool has_name() const;
  private:
  bool _internal_has_name() const;
  public:
  void clear_name();
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  std::string* unsafe_arena_release_name();
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_name(
      std::string* name);
  private:
  const std::string& _internal_name() const;
  void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // optional int32 id = 1;
  bool has_id() const;
  private:
  bool _internal_has_id() const;
  public:
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::int32 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:SolasMatch.Common.Protobufs.Models.Language)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr code_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::PROTOBUF_NAMESPACE_ID::int32 id_;
  friend struct ::TableStruct_Language_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Language

// optional int32 id = 1;
inline bool Language::_internal_has_id() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool Language::has_id() const {
  return _internal_has_id();
}
inline void Language::clear_id() {
  id_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Language::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Language::id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.Language.id)
  return _internal_id();
}
inline void Language::_internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  id_ = value;
}
inline void Language::set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Models.Language.id)
}

// optional string code = 2;
inline bool Language::_internal_has_code() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Language::has_code() const {
  return _internal_has_code();
}
inline void Language::clear_code() {
  code_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& Language::code() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.Language.code)
  return _internal_code();
}
inline void Language::set_code(const std::string& value) {
  _internal_set_code(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Models.Language.code)
}
inline std::string* Language::mutable_code() {
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Models.Language.code)
  return _internal_mutable_code();
}
inline const std::string& Language::_internal_code() const {
  return code_.Get();
}
inline void Language::_internal_set_code(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  code_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void Language::set_code(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  code_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:SolasMatch.Common.Protobufs.Models.Language.code)
}
inline void Language::set_code(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  code_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:SolasMatch.Common.Protobufs.Models.Language.code)
}
inline void Language::set_code(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  code_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:SolasMatch.Common.Protobufs.Models.Language.code)
}
inline std::string* Language::_internal_mutable_code() {
  _has_bits_[0] |= 0x00000001u;
  return code_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* Language::release_code() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Models.Language.code)
  if (!_internal_has_code()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return code_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Language::set_allocated_code(std::string* code) {
  if (code != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  code_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), code,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Models.Language.code)
}
inline std::string* Language::unsafe_arena_release_code() {
  // @@protoc_insertion_point(field_unsafe_arena_release:SolasMatch.Common.Protobufs.Models.Language.code)
  GOOGLE_DCHECK(GetArena() != nullptr);
  _has_bits_[0] &= ~0x00000001u;
  return code_.UnsafeArenaRelease(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      GetArena());
}
inline void Language::unsafe_arena_set_allocated_code(
    std::string* code) {
  GOOGLE_DCHECK(GetArena() != nullptr);
  if (code != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  code_.UnsafeArenaSetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      code, GetArena());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SolasMatch.Common.Protobufs.Models.Language.code)
}

// optional string name = 3;
inline bool Language::_internal_has_name() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Language::has_name() const {
  return _internal_has_name();
}
inline void Language::clear_name() {
  name_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& Language::name() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.Language.name)
  return _internal_name();
}
inline void Language::set_name(const std::string& value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Models.Language.name)
}
inline std::string* Language::mutable_name() {
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Models.Language.name)
  return _internal_mutable_name();
}
inline const std::string& Language::_internal_name() const {
  return name_.Get();
}
inline void Language::_internal_set_name(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void Language::set_name(std::string&& value) {
  _has_bits_[0] |= 0x00000002u;
  name_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:SolasMatch.Common.Protobufs.Models.Language.name)
}
inline void Language::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000002u;
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:SolasMatch.Common.Protobufs.Models.Language.name)
}
inline void Language::set_name(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000002u;
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:SolasMatch.Common.Protobufs.Models.Language.name)
}
inline std::string* Language::_internal_mutable_name() {
  _has_bits_[0] |= 0x00000002u;
  return name_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* Language::release_name() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Models.Language.name)
  if (!_internal_has_name()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return name_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Language::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Models.Language.name)
}
inline std::string* Language::unsafe_arena_release_name() {
  // @@protoc_insertion_point(field_unsafe_arena_release:SolasMatch.Common.Protobufs.Models.Language.name)
  GOOGLE_DCHECK(GetArena() != nullptr);
  _has_bits_[0] &= ~0x00000002u;
  return name_.UnsafeArenaRelease(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      GetArena());
}
inline void Language::unsafe_arena_set_allocated_name(
    std::string* name) {
  GOOGLE_DCHECK(GetArena() != nullptr);
  if (name != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  name_.UnsafeArenaSetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      name, GetArena());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SolasMatch.Common.Protobufs.Models.Language.name)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Language_2eproto
