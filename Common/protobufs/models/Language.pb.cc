// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Language.proto

#include "Language.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {
class LanguageDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Language> _instance;
} _Language_default_instance_;
}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
static void InitDefaultsscc_info_Language_Language_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::SolasMatch::Common::Protobufs::Models::_Language_default_instance_;
    new (ptr) ::SolasMatch::Common::Protobufs::Models::Language();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::SolasMatch::Common::Protobufs::Models::Language::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Language_Language_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Language_Language_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Language_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Language_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Language_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Language_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::Language, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::Language, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::Language, id_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::Language, code_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::Language, name_),
  2,
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, sizeof(::SolasMatch::Common::Protobufs::Models::Language)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::SolasMatch::Common::Protobufs::Models::_Language_default_instance_),
};

const char descriptor_table_protodef_Language_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016Language.proto\022\"SolasMatch.Common.Prot"
  "obufs.Models\"2\n\010Language\022\n\n\002id\030\001 \001(\005\022\014\n\004"
  "code\030\002 \001(\t\022\014\n\004name\030\003 \001(\t"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_Language_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_Language_2eproto_sccs[1] = {
  &scc_info_Language_Language_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Language_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Language_2eproto = {
  false, false, descriptor_table_protodef_Language_2eproto, "Language.proto", 104,
  &descriptor_table_Language_2eproto_once, descriptor_table_Language_2eproto_sccs, descriptor_table_Language_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_Language_2eproto::offsets,
  file_level_metadata_Language_2eproto, 1, file_level_enum_descriptors_Language_2eproto, file_level_service_descriptors_Language_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Language_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_Language_2eproto)), true);
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {

// ===================================================================

void Language::InitAsDefaultInstance() {
}
class Language::_Internal {
 public:
  using HasBits = decltype(std::declval<Language>()._has_bits_);
  static void set_has_id(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_code(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

Language::Language(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:SolasMatch.Common.Protobufs.Models.Language)
}
Language::Language(const Language& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_code()) {
    code_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_code(),
      GetArena());
  }
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_name()) {
    name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_name(),
      GetArena());
  }
  id_ = from.id_;
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Models.Language)
}

void Language::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Language_Language_2eproto.base);
  code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  id_ = 0;
}

Language::~Language() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Models.Language)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Language::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  code_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Language::ArenaDtor(void* object) {
  Language* _this = reinterpret_cast< Language* >(object);
  (void)_this;
}
void Language::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Language::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Language& Language::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Language_Language_2eproto.base);
  return *internal_default_instance();
}


void Language::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Models.Language)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      code_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      name_.ClearNonDefaultToEmpty();
    }
  }
  id_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Language::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional int32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_id(&has_bits);
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional string code = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_code();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "SolasMatch.Common.Protobufs.Models.Language.code");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional string name = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "SolasMatch.Common.Protobufs.Models.Language.name");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Language::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Models.Language)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 id = 1;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_id(), target);
  }

  // optional string code = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_code().data(), static_cast<int>(this->_internal_code().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Models.Language.code");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_code(), target);
  }

  // optional string name = 3;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Models.Language.name");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Models.Language)
  return target;
}

size_t Language::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Models.Language)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    // optional string code = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_code());
    }

    // optional string name = 3;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_name());
    }

    // optional int32 id = 1;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_id());
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Language::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Models.Language)
  GOOGLE_DCHECK_NE(&from, this);
  const Language* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Language>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Models.Language)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Models.Language)
    MergeFrom(*source);
  }
}

void Language::MergeFrom(const Language& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Models.Language)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_code(from._internal_code());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_set_name(from._internal_name());
    }
    if (cached_has_bits & 0x00000004u) {
      id_ = from.id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Language::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Models.Language)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Language::CopyFrom(const Language& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Models.Language)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Language::IsInitialized() const {
  return true;
}

void Language::InternalSwap(Language* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  code_.Swap(&other->code_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(id_, other->id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Language::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::SolasMatch::Common::Protobufs::Models::Language* Arena::CreateMaybeMessage< ::SolasMatch::Common::Protobufs::Models::Language >(Arena* arena) {
  return Arena::CreateMessageInternal< ::SolasMatch::Common::Protobufs::Models::Language >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
